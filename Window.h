#ifndef _PROGJOGOS_WINDOW_H_
#define _PROGJOGOS_WINDOW_H_

#include <windows.h>
#include <windowsx.h>   // inclui extensões do windows
// ---------------------------------------------------------------------------------
// Constantes globais e enumerações
enum WindowModes { FULLSCREEN, WINDOWED, BORDERLESS };


// ---------------------------------------------------------------------------------

class Window
{
private:
    HINSTANCE   hInstance;                                  // identificador da aplicação
    HWND        windowHandle;                               // identificador da janela    
    int         windowWidth;                                // largura da janela
    int         windowHeight;                               // altura da janela
    HICON       windowIcon;                                 // ícone da janela
    HCURSOR     windowCursor;                               // cursor da janela
    COLORREF    windowColor;                                // cor de fundo da janela
    LPCSTR      windowTitle;                                // nome da barra de título
    DWORD       windowStyle;                                // estilo da janela 
    int         windowMode;                                 // modo tela cheia, em janela ou sem borda
    int         windowPosX;                                 // posição inicial da janela no eixo x
    int         windowPosY;                                 // posição inicial da janela no eixo y
    float       windowCenterX;                              // centro da janela no eixo x
    float       windowCenterY;                              // centro da janela no eixo y
    static int  windowMouseX;                               // posição do mouse eixo x
    static int  windowMouseY;                               // posição do mouse eixo y
    static int  windowMouseWheel;                           // giro da roda do mouse


public:
    Window();                                               // construtor de Window

    HINSTANCE AppId();                                      // retorna o identificador da aplicação
    HWND Id();                                              // retorna o identificador da janela
    float Width();                                          // retorna a largura atual da janela
    float Height();                                         // retorna a altura atual da janela

    void Icon(const char* icon);                             // define o ícone da janela
    void Cursor(const char* cursor);                         // define o cursor da janela
    void Title(const LPCSTR title);                         // define o título da janela 
    void Size(int width, int height);                       // define o tamanho (largura e altura) da janela
    void Mode(int mode);                                    // define o modo da janela (FULLSCREEN/WINDOWED)

    int  Mode() const;                                      // retorna o modo atual da janela (FULLSCREEN/WINDOWED)
    float CenterX() const;                                  // retorna o centro da janela no eixo x
    float CenterY() const;                                  // retorna o centro da janela no eixo y
    LPCSTR Title() const;                                   // retorna título da janela

    void HideCursor(bool hide);                             // habilita ou desabilita a exbição do cursor
    void Close();                                           // fecha janela imediatamente

    float MouseX();                                         // retorna posição x do mouse
    float MouseY();                                         // retorna posição y do mouse
    int MouseWheel();                                       // retorna giro da roda do mouse

    COLORREF Color();                                       // retorna a cor de fundo da janela
    void Color(int r, int g, int b);                        // define a cor de fundo da janela
    bool Create();                                          // cria a janela com os valores dos atributos

 };

// ---------------------------------------------------------------------------------
static Window* window;

// Funções Membro Inline

// retorna identificador da aplicação
inline HINSTANCE Window::AppId()
{
    return hInstance;
}

// retorna o identificador da janela do jogo
inline HWND Window::Id()
{
    return windowHandle;
}

// retorna a largura atual da janela
inline float Window::Width()
{
    return float(windowWidth);
}

// retorna a altura atual da janela
inline float Window::Height()
{
    return float(windowHeight);
}

// ----------------------------------------------------------

// define o ícone da janela
inline void Window::Icon(const char* icon)
{
    windowIcon = (HICON)LoadImage(NULL, icon, IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
}

// define o cursor da janela
inline void Window::Cursor(const char* cursor)
{
    windowCursor = (HCURSOR)LoadImage(NULL, cursor, IMAGE_CURSOR, 32, 32, LR_LOADFROMFILE);
}

// define o título da janela 
inline void Window::Title(const LPCSTR title)
{
    windowTitle = title;
}

// -----------------------------------------------------------

// retorna o modo atual da janela (FULLSCREEN/WINDOWED)
inline int Window::Mode() const
{
    return windowMode;
}

// retorna o centro da janela no eixo horizontal
inline float Window::CenterX() const
{
    return windowCenterX;
}

// retorna o centro da janela no eixo vertical
inline float Window::CenterY() const
{
    return windowCenterY;
}

// retorna título da janela
inline LPCSTR Window::Title() const
{
    return windowTitle;
}

// -----------------------------------------------------------

// habilita ou desabilita a exbição do cursor
inline void Window::HideCursor(bool hide)
{
    ShowCursor(!hide);
}

// fecha a janela imediatamente 
inline void Window::Close()
{
    PostMessage(windowHandle, WM_DESTROY, 0, 0);
}

// retorna a posição do mouse no eixo x
inline float Window::MouseX()
{
    return float(windowMouseX);
}

// retorna a posição do mouse no eixo y
inline float Window::MouseY()
{
    return float(windowMouseY);
}

// retorna giro da roda do mouse
inline int Window::MouseWheel()
{
    return windowMouseWheel;
}

// -----------------------------------------------------------

// retorna a cor de fundo da janela
inline COLORREF Window::Color()
{
    return windowColor;
}

// define a cor de fundo da janela
inline void Window::Color(int r, int g, int b)
{
    windowColor = RGB(r, g, b);
}

// ---------------------------------------------------------------------------------


#endif
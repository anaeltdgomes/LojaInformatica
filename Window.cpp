#include "Window.h"

// -------------------------------------------------------------------------------
// Inicializa��o de membros est�ticos da classe
int  Window::windowMouseX = 0;                              // posi��o do mouse no eixo x
int  Window::windowMouseY = 0;                              // posi��o do mouse no eixo y
int  Window::windowMouseWheel = 0;                          // giro da roda do mouse

// -------------------------------------------------------------------------------
// Construtor

Window::Window()
{
    hInstance = GetModuleHandle(NULL);              // identificador da aplica��o
    windowHandle = 0;                               // identificador da janela do jogo
    windowWidth = GetSystemMetrics(SM_CXSCREEN);    // a janela ocupa toda a tela (tela cheia)
    windowHeight = GetSystemMetrics(SM_CYSCREEN);   // a janela ocupa toda a tela (tela cheia)
    windowIcon = LoadIcon(NULL, IDI_APPLICATION);   // �cone padr�o de uma aplica��o
    windowCursor = LoadCursor(NULL, IDC_ARROW);     // cursor padr�o de uma aplica��o
    windowColor = RGB(0, 0, 0);                     // cor de fundo padr�o � preta
    windowTitle = "Basic Window";                   // t�tulo padr�o da janela
    windowStyle = WS_POPUP | WS_VISIBLE;            // estilo para tela cheia
    windowMode = FULLSCREEN;                        // modo padr�o � tela cheia
    windowPosX = 0;                                 // posi��o inicial da janela no eixo x
    windowPosY = 0;                                 // posi��o inicial da janela no eixo y
    windowCenterX = windowWidth / 2.0f;             // centro da janela no eixo x
    windowCenterY = windowHeight / 2.0f;            // centro da janela no eixo y
}

// -------------------------------------------------------------------------------

void Window::Mode(int mode)
{
    windowMode = mode;

    if (mode == WINDOWED)
    {
        // modo em janela
        windowStyle = WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE;
    }
    else
    {
        // modo em tela cheia ou sem bordas
        windowStyle = WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE;
    }
}

// -------------------------------------------------------------------------------

void Window::Size(int width, int height)
{
    // window size
    windowWidth = width;
    windowHeight = height;

    // calcula a posi��o do centro da janela
    windowCenterX = windowWidth / 2.0f;
    windowCenterY = windowHeight / 2.0f;

    // ajusta a posi��o da janela para o centro da tela
    windowPosX = GetSystemMetrics(SM_CXSCREEN) / 2 - windowWidth / 2;
    windowPosY = GetSystemMetrics(SM_CYSCREEN) / 2 - windowHeight / 2;
}

// -------------------------------------------------------------------------------

bool Window::Create()
{
    // tratamento de eventos do Windows
    LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    WNDCLASSEX wndClass;

    // definindo uma classe de janela chamada "GameWindow"
    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WndProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = windowIcon;
    wndClass.hCursor = windowCursor;
    wndClass.hbrBackground = (HBRUSH)CreateSolidBrush(windowColor);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = "GameWindow";
    wndClass.hIconSm = windowIcon;

    // registrando "GameWindow"
    if (!RegisterClassEx(&wndClass))
        return false;

    // criando uma janela baseada na classe "GameWindow" 
    windowHandle = CreateWindowEx(
        NULL,                           // estilos extras
        "GameWindow",                  // nome da "window class"
        windowTitle,                    // t�tulo da janela
        windowStyle,                    // estilo da janela
        windowPosX, windowPosY,         // posi��o (x,y) inicial
        windowWidth, windowHeight,      // largura e altura da janela
        NULL,                           // identificador da janela pai
        NULL,                           // identificador do menu
        hInstance,                      // identificador da aplica��o
        NULL);                          // par�metros de cria��o

    
    // Ao usar o modo em janela � preciso levar em conta que as barras 
    // e bordas ocupam espa�o na janela. O c�digo abaixo ajusta o tamanho
    // da janela de forma que a �rea cliente do jogo fique no tamanho 
    // (windowWidth x windowHeight)

    if (windowMode == WINDOWED)
    {
        // ret�ngulo com o tamanho da �rea cliente desejada
        RECT winRect = { 0, 0, windowWidth, windowHeight };

        // ajusta o tamanho do ret�ngulo
        AdjustWindowRectEx(&winRect,
            GetWindowStyle(windowHandle),
            GetMenu(windowHandle) != NULL,
            GetWindowExStyle(windowHandle));

        // atualiza posi��o da janela
        windowPosX = GetSystemMetrics(SM_CXSCREEN) / 2 - (winRect.right - winRect.left) / 2;
        windowPosY = GetSystemMetrics(SM_CYSCREEN) / 2 - (winRect.bottom - winRect.top) / 2;

        // redimensiona janela com uma chamada a MoveWindow
        MoveWindow(
            windowHandle,                  // identificador da janela
            windowPosX,                    // posi��o x
            windowPosY,                    // posi��o y
            winRect.right - winRect.left,  // largura
            winRect.bottom - winRect.top,  // altura
            TRUE);                         // repintar
    }

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // retorna estado da inicializa��o (bem sucedida ou n�o)
    //return (windowHandle ? true : false);

    return (int)msg.wParam;
}


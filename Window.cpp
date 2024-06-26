#include "Window.h"

// -------------------------------------------------------------------------------
// Inicialização de membros estáticos da classe
int  Window::windowMouseX = 0;                              // posição do mouse no eixo x
int  Window::windowMouseY = 0;                              // posição do mouse no eixo y
int  Window::windowMouseWheel = 0;                          // giro da roda do mouse

// -------------------------------------------------------------------------------
// Construtor

Window::Window()
{
    hInstance = GetModuleHandle(NULL);              // identificador da aplicação
    windowHandle = 0;                               // identificador da janela do jogo
    windowWidth = GetSystemMetrics(SM_CXSCREEN);    // a janela ocupa toda a tela (tela cheia)
    windowHeight = GetSystemMetrics(SM_CYSCREEN);   // a janela ocupa toda a tela (tela cheia)
    windowIcon = LoadIcon(NULL, IDI_APPLICATION);   // ícone padrão de uma aplicação
    windowCursor = LoadCursor(NULL, IDC_ARROW);     // cursor padrão de uma aplicação
    windowColor = RGB(0, 0, 0);                     // cor de fundo padrão é preta
    windowTitle = "Basic Window";                   // título padrão da janela
    windowStyle = WS_POPUP | WS_VISIBLE;            // estilo para tela cheia
    windowMode = FULLSCREEN;                        // modo padrão é tela cheia
    windowPosX = 0;                                 // posição inicial da janela no eixo x
    windowPosY = 0;                                 // posição inicial da janela no eixo y
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

    // calcula a posição do centro da janela
    windowCenterX = windowWidth / 2.0f;
    windowCenterY = windowHeight / 2.0f;

    // ajusta a posição da janela para o centro da tela
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
        windowTitle,                    // título da janela
        windowStyle,                    // estilo da janela
        windowPosX, windowPosY,         // posição (x,y) inicial
        windowWidth, windowHeight,      // largura e altura da janela
        NULL,                           // identificador da janela pai
        NULL,                           // identificador do menu
        hInstance,                      // identificador da aplicação
        NULL);                          // parâmetros de criação

    
    // Ao usar o modo em janela é preciso levar em conta que as barras 
    // e bordas ocupam espaço na janela. O código abaixo ajusta o tamanho
    // da janela de forma que a área cliente do jogo fique no tamanho 
    // (windowWidth x windowHeight)

    if (windowMode == WINDOWED)
    {
        // retângulo com o tamanho da área cliente desejada
        RECT winRect = { 0, 0, windowWidth, windowHeight };

        // ajusta o tamanho do retângulo
        AdjustWindowRectEx(&winRect,
            GetWindowStyle(windowHandle),
            GetMenu(windowHandle) != NULL,
            GetWindowExStyle(windowHandle));

        // atualiza posição da janela
        windowPosX = GetSystemMetrics(SM_CXSCREEN) / 2 - (winRect.right - winRect.left) / 2;
        windowPosY = GetSystemMetrics(SM_CYSCREEN) / 2 - (winRect.bottom - winRect.top) / 2;

        // redimensiona janela com uma chamada a MoveWindow
        MoveWindow(
            windowHandle,                  // identificador da janela
            windowPosX,                    // posição x
            windowPosY,                    // posição y
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

    // retorna estado da inicialização (bem sucedida ou não)
    //return (windowHandle ? true : false);

    return (int)msg.wParam;
}


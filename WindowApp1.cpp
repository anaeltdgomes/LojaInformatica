#include "framework.h"
#include "WindowApp1.h"

#include "Functions.h" // Funções usadas várias vezes no código


#define MAX_LOADSTRING 100

// Variáveis Globais:
HINSTANCE hInst;                                // instância atual
const char* szTitle = "Minha Loja.";            // O texto da barra de título
WCHAR szWindowClass[MAX_LOADSTRING];            // o nome da classe da janela principal

HWND Panelhwnd, PanelCalender, PanelContact, PanelConsult, PanelEmployee, PanelSale;
HBITMAP introBG, calenderBG, contactBG, monthImg, productImgView, quadro1Img, btnNextImg, btnPrevImg;
BITMAP introBitMap, contactBitMap, calenderBitMap, monthImgBitMap, productImgViewBitMap;
BITMAP quadro1ImgBitMap;
Later* myDelay;
AnyButton* shutdown, *addEmployeeBtn, *btnNext, *btnPrev;
Label* myLabel, *myLabel2, *myLabel3, *myLabel4, *myLabelMarca, *myLabelNovoEmployee, * myLabelVendas;
Label* vendasTxtID, *vendasTxtProduto, *vendasTxtQuantidade, *vendasTxtVendedor, *vendasTxtDate, *vendasTxtPreco, *vendasTxtTotal;
MonthCalendar* myMonthCalendar;
Edit* myEditBox, * addEmployeeEdit, * addEmployeeSexEdit, * addEmployeeAgeEdit;
Edit* addEmployeeJobEdit, * addEmployeeSalaryEdit, * addEmployeeAdmissionEdit;
ComboBox* myComboBox;
ListView* myListView, *myListView2;
TabControl* myTab;

extern RECT mainWindowRec = { 0 }; // Possibilita a variável ser usada em outros arquivos
int clientWindowCenterX, clientWindowCenterY;
int centerSystemX = GetSystemMetrics(SM_CXSCREEN) / 2 - 1000 / 2;
int centerSystemY = GetSystemMetrics(SM_CYSCREEN) / 2 - 600 / 2;
int timerCount = 0, timerCountMax = 0;
int addPosX = 0, addPosY = 0, addWidth = 0, addHeight = 0;  // Usado em SetTimer()
int productImgViewPosX = 650;
extern int contadorVendas = 1;
stringstream comboStr;

// Valores usados no painel de vendas para posicionamento
int posX210 = 210;
int posX20 = 20;
int posX340 = 340;
int posX270 = 270;
int posX140 = 140;
int posY230 = 230;
int posY40 = 40;
int posY100 = 100;
int posY160 = 160;
int posY270 = 270;

// Declarações de encaminhamento de funções incluídas nesse módulo de código:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK WndProcPanel(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProcPanelCalender(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProcPanelContact(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProcPanelConsult(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProcPanelEmployee(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProcPanelSale(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Inicializar cadeias de caracteres globais
    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWAPP1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Realize a inicialização do aplicativo:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWAPP1));

    MSG msg;

    // Loop de mensagem principal:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}
//
//  FUNÇÃO: MyRegisterClass()
//
//  FINALIDADE: Registra a classe de janela.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWAPP1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWAPP1);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    RegisterClassExW(&wcex);

    wcex.lpfnWndProc = WndProcPanel;
    wcex.hbrBackground = NULL;
    wcex.lpszClassName = L"PanelIntro";
    RegisterClassExW(&wcex);

    wcex.lpfnWndProc = WndProcPanelCalender;
    wcex.hbrBackground = NULL;
    wcex.lpszClassName = L"PanelCalender";
    RegisterClassExW(&wcex);

    wcex.lpfnWndProc = WndProcPanelContact;
    wcex.hbrBackground = NULL;
    wcex.lpszClassName = L"PanelContact";
    RegisterClassExW(&wcex);

    wcex.lpfnWndProc = WndProcPanelConsult;
    wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(200, 200, 200)));
    wcex.lpszClassName = L"PanelConsult";
    RegisterClassExW(&wcex);

    wcex.lpfnWndProc = WndProcPanelEmployee;
    wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(200, 200, 200)));
    wcex.lpszClassName = L"PanelEmployee";
    RegisterClassExW(&wcex);

    wcex.lpfnWndProc = WndProcPanelSale;
    wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(200, 200, 200)));
    wcex.lpszClassName = L"PanelSale";
    RegisterClassExW(&wcex);
    
    return true;
}
//
//   FUNÇÃO: InitInstance(HINSTANCE, int)
//
//   FINALIDADE: Salva o identificador de instância e cria a janela principal
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Armazenar o identificador de instância em nossa variável global

    HWND hWnd = CreateWindowW(szWindowClass, (LPCWSTR)szTitle, WS_OVERLAPPEDWINDOW,
        centerSystemX, centerSystemY, 1000, 600, nullptr, nullptr, hInstance, nullptr);
        
    GetClientRect(hWnd, &mainWindowRec);

    // Create container panel
    Panelhwnd = CreateWindowEx(NULL, "PanelIntro", "Panel1", WS_CHILD | WS_CLIPSIBLINGS |
        WS_CLIPCHILDREN | WS_VISIBLE, 0, 0, 1000, 550, hWnd, (HMENU)ID_PANEL1,
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

    PanelCalender = CreateWindowEx(NULL, "PanelCalender", "Panel2", WS_CHILD | WS_CLIPSIBLINGS |
        WS_CLIPCHILDREN | WS_VISIBLE, 0, 0, 1000, 550, hWnd, (HMENU)ID_PANEL2,
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

    PanelContact = CreateWindowEx(NULL, "PanelContact", "Panel3", WS_CHILD | WS_CLIPSIBLINGS |
        WS_CLIPCHILDREN | WS_VISIBLE, 0, 0, 1000, 550, hWnd, (HMENU)ID_PANEL3,
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
    
    PanelConsult = CreateWindowEx(NULL, "PanelConsult", "Panel4", WS_CHILD | WS_CLIPSIBLINGS |
        WS_CLIPCHILDREN | WS_VISIBLE, 0, 0, 1000, 600, hWnd, (HMENU)ID_PANEL4,
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

    PanelEmployee = CreateWindowEx(NULL, "PanelEmployee", "Panel5", WS_CHILD | WS_CLIPSIBLINGS |
        WS_CLIPCHILDREN | WS_VISIBLE, 0, 0, 1000, 600, hWnd, (HMENU)ID_PANEL5,
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

    PanelSale = CreateWindowEx(NULL, "PanelSale", "Panel6", WS_CHILD | WS_CLIPSIBLINGS |
        WS_CLIPCHILDREN | WS_VISIBLE, 0, 0, 1000, 600, hWnd, (HMENU)ID_PANEL6,
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

    if (!hWnd)
    {
        return FALSE;
    }
    
    ShowWindow(hWnd, nCmdShow);
    ShowWindow(Panelhwnd, 1);
    UpdateWindow(hWnd);
    UpdateWindow(Panelhwnd);
    ShowWindow(PanelCalender, 0);
    ShowWindow(PanelContact, 0);
    ShowWindow(PanelConsult, 0);
    ShowWindow(PanelEmployee, 0);
    ShowWindow(PanelSale, 0);

    return TRUE;
}

//  FUNÇÃO: WndProc(HWND, UINT, WPARAM, LPARAM)

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE: 
    {
        shutdown = new AnyButton(hWnd, ID_SHUTDOWN, " ", 30, mainWindowRec.bottom - 58, 100, 54, WS_VISIBLE | WS_CHILD | BS_TEXT | BS_CENTER);
        HICON hIcon1 = (HICON)LoadImage(NULL, "Resources\\shutdown.ico", IMAGE_ICON, 64, 64, LR_LOADFROMFILE);
        SendMessage(shutdown->hAnyButton, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)hIcon1);

        return 0;
    }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Analise as seleções do menu:
        switch (wmId)
        {
        case ID_INTRO:
        {
            ShowWindow(Panelhwnd, 1);
            ShowWindow(PanelCalender, 0);
            ShowWindow(PanelContact, 0);
            ShowWindow(PanelConsult, 0);
            ShowWindow(PanelEmployee, 0);
            ShowWindow(PanelSale, 0);
        }
            break;
        case ID_CALENDER:
        {
            ShowWindow(Panelhwnd, 0);
            ShowWindow(PanelCalender, 1);
            ShowWindow(PanelContact, 0);
            ShowWindow(PanelConsult, 0);
            ShowWindow(PanelEmployee, 0);
            ShowWindow(PanelSale, 0);
        }
        break;
        case ID_CONTACT:
        {
            ShowWindow(Panelhwnd, 0);
            ShowWindow(PanelCalender, 0);
            ShowWindow(PanelContact, 1);
            ShowWindow(PanelConsult, 0);
            ShowWindow(PanelEmployee, 0);
            ShowWindow(PanelSale, 0);
        }
        break;
        case ID_CONSULT:
        {
            ShowWindow(Panelhwnd, 0);
            ShowWindow(PanelCalender, 0);
            ShowWindow(PanelContact, 0);
            ShowWindow(PanelConsult, 1);
            ShowWindow(PanelEmployee, 0);
            ShowWindow(PanelSale, 0);
        }
        break;
        case ID_ENPLOYEE:
        {
            ShowWindow(Panelhwnd, 0);
            ShowWindow(PanelCalender, 0);
            ShowWindow(PanelContact, 0);
            ShowWindow(PanelConsult, 0);
            ShowWindow(PanelEmployee, 1);
            ShowWindow(PanelSale, 0);
        }
        break;
        case ID_SALE:
        {
            ShowWindow(Panelhwnd, 0);
            ShowWindow(PanelCalender, 0);
            ShowWindow(PanelContact, 0);
            ShowWindow(PanelConsult, 0);
            ShowWindow(PanelEmployee, 0);
            ShowWindow(PanelSale, 1);
        }
        break;

        case ID_SHUTDOWN:
            DestroyWindow(hWnd);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_SIZE: 
    {
        GetClientRect(hWnd, &mainWindowRec);
        SetWindowPos(Panelhwnd, HWND_BOTTOM, 0,0, mainWindowRec.right, mainWindowRec.bottom, NULL);
        SetWindowPos(PanelCalender, HWND_BOTTOM, 0, 0, mainWindowRec.right, mainWindowRec.bottom, NULL);
        SetWindowPos(PanelContact, HWND_BOTTOM, 0, 0, mainWindowRec.right, mainWindowRec.bottom, NULL);
        SetWindowPos(PanelConsult, HWND_BOTTOM, 0, 0, mainWindowRec.right, mainWindowRec.bottom, NULL);
        SetWindowPos(PanelEmployee, HWND_BOTTOM, 0, 0, mainWindowRec.right, mainWindowRec.bottom, NULL);
        SetWindowPos(PanelSale, HWND_BOTTOM, 0, 0, mainWindowRec.right, mainWindowRec.bottom, NULL);
        SetWindowPos(shutdown->hAnyButton, HWND_TOP, mainWindowRec.left + 20, mainWindowRec.bottom - 58,
            returnWidth(shutdown->hAnyButton), returnHeight(shutdown->hAnyButton), NULL);
        SetWindowPos(myLabel4->hLabel, HWND_TOP, mainWindowRec.right - 150, mainWindowRec.bottom - 100, 150, 75, NULL);

        // Imagem de fundo inicial
        introBG = (HBITMAP)LoadImage(NULL, "Resources\\IntroBG.bmp", IMAGE_BITMAP, mainWindowRec.right, mainWindowRec.bottom, LR_LOADFROMFILE);
        contactBG = (HBITMAP)LoadImage(NULL, "Resources\\ContatoBG.bmp", IMAGE_BITMAP, mainWindowRec.right, mainWindowRec.bottom, LR_LOADFROMFILE);
        calenderBG = (HBITMAP)LoadImage(NULL, "Resources\\CalendarioBG.bmp", IMAGE_BITMAP, mainWindowRec.right, mainWindowRec.bottom, LR_LOADFROMFILE);
        
        // Mantém o painel de vendas centralizado
        clientWindowCenterX = mainWindowRec.right / 2;
        clientWindowCenterY = mainWindowRec.bottom / 2;
        MoveWindow(vendasTxtID->hLabel, posX210 + (clientWindowCenterX - 250), posY230 + (clientWindowCenterY - 165), 95, 25, true);
        MoveWindow(vendasTxtProduto->hLabel, posX20 + (clientWindowCenterX - 250), posY40 + (clientWindowCenterY - 165), 300, 50, true);
        MoveWindow(vendasTxtQuantidade->hLabel, posX340 + (clientWindowCenterX - 250), posY40 + (clientWindowCenterY - 165), 100, 30, true);
        MoveWindow(vendasTxtVendedor->hLabel, posX20 + (clientWindowCenterX - 250), posY100 + (clientWindowCenterY - 165), 300, 30, true);
        MoveWindow(vendasTxtDate->hLabel, posX340 + (clientWindowCenterX - 250), posY100 + (clientWindowCenterY - 165), 150, 30, true);
        MoveWindow(vendasTxtPreco->hLabel, posX20 + (clientWindowCenterX - 250), posY160 + (clientWindowCenterY - 165), 130, 40, true);
        MoveWindow(vendasTxtTotal->hLabel, posX340 + (clientWindowCenterX - 250), posY160 + (clientWindowCenterY - 165), 130, 40, true);
        MoveWindow(btnNext->hAnyButton, posX270 + (clientWindowCenterX - 250), posY270 + (clientWindowCenterY - 165), 110, 34, true);
        MoveWindow(btnPrev->hAnyButton, posX140 + (clientWindowCenterX - 250), posY270 + (clientWindowCenterY - 165), 110, 34, true);

        // Amplia o ListView dos produtos no PanelConsult de acordo com o tamanho da janela
        if (mainWindowRec.right >= 1001) {
            SetWindowPos(myListView->hListView, HWND_TOP, 10, 50, 600 + (mainWindowRec.right - 1000) , 400, NULL);
            SetWindowPos(myListView2->hListView, HWND_TOP, 12, 40, 650 + (mainWindowRec.right - 1000), 250, NULL);
            SetWindowPos(myTab->hTab, HWND_BOTTOM, 8, 10, 662 + (mainWindowRec.right - 1000), 290, NULL);
            productImgViewPosX = 650 + (mainWindowRec.right - 1000);
        }
        else if (mainWindowRec.right <= 1000) {
            SetWindowPos(myListView->hListView, HWND_TOP, 10, 50, 600, 400, NULL);
            SetWindowPos(myListView2->hListView, HWND_TOP, 12, 40, 650, 250, NULL);
            SetWindowPos(myTab->hTab, HWND_BOTTOM, 8, 10, 662, 290, NULL);
            productImgViewPosX = 650;
        }
    }
    break;
    case WM_DESTROY:
        delete(myDelay);
        delete(addEmployeeBtn);
        delete(shutdown);
        delete(Panelhwnd);
        delete(PanelCalender);
        delete(PanelContact);
        delete(PanelConsult);
        delete(PanelEmployee);
        delete(PanelSale);
        delete(myLabel);
        delete(myLabel2);
        delete(myLabel3);
        delete(myLabel4);
        delete(myLabelMarca);
        delete(myLabelVendas);
        delete(vendasTxtID);
        delete(vendasTxtProduto);
        delete(vendasTxtQuantidade);
        delete(vendasTxtVendedor);
        delete(vendasTxtDate);
        delete(vendasTxtPreco);
        delete(vendasTxtTotal);
        delete(introBG);
        delete(calenderBG);
        delete(contactBG);
        delete(monthImg);
        delete(myMonthCalendar);
        delete(myEditBox);
        delete(myComboBox);
        delete(myListView);
        delete(myListView2);
        delete(&comboStr);
        delete(addEmployeeEdit);
        delete(addEmployeeSexEdit);
        delete(addEmployeeAgeEdit);
        delete(addEmployeeJobEdit);
        delete(addEmployeeSalaryEdit);
        delete(addEmployeeAdmissionEdit);
        delete(myTab);
        delete(&introBG);
        delete(&calenderBG);
        delete(&contactBG);
        delete(&monthImg);
        delete(productImgView);
        delete(&introBitMap);
        delete(&contactBitMap);
        delete(&calenderBitMap);
        delete(&monthImgBitMap);
        delete(&productImgViewBitMap);
        delete(&quadro1ImgBitMap);
        delete(quadro1Img);
        delete(btnNextImg);
        delete(btnPrevImg);
        delete(btnNext);
        delete(btnPrev);


        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


/*--------------------------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProcPanelEmployee(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        myTab = new TabControl(hwnd, ID_TAB1, 8, 10, 662, 290);
        myTab->AddTab("Inativo");
        myTab->AddTab("Ativo");
        TabCtrl_SetCurSel(myTab->hTab, 0); // Foca na aba 'Ativo'

        myListView2 = new ListView(hwnd, ID_LISTVIEW2, 12, 40, 650, 250);
        ListView_SetExtendedListViewStyle(myListView2->hListView, LVS_EX_FULLROWSELECT);
        myListView2->MakeTransparent();

        myLabelNovoEmployee = new Label(hwnd, ID_LABEL6, "Novo funcionário: ", 20, 330, 150, 25);
        myLabelNovoEmployee->setFont("Arial", 20);

        addEmployeeEdit = new Edit(hwnd, ID_EDIT_NAME, "Nome do Funcionário", 20, 355, 190, 30);
        addEmployeeSexEdit = new Edit(hwnd, ID_EDIT_SEX, "Sexo", 220, 355, 100, 30);
        addEmployeeAgeEdit = new Edit(hwnd, ID_EDIT_AGE, "Idade", 330, 355, 50, 30);
        addEmployeeJobEdit = new Edit(hwnd, ID_EDIT_JOB, "Cargo", 390, 355, 100, 30);
        addEmployeeSalaryEdit = new Edit(hwnd, ID_EDIT_SALARY, "Salário", 500, 355, 70, 30);
        addEmployeeAdmissionEdit = new Edit(hwnd, ID_EDIT_ADMISSION, "Data de Admissão", 580, 355, 150, 30);

        addEmployeeBtn = new AnyButton(hwnd, ID_ADDEMPLOYEE1, "Adicionar", 20, 395, 100, 25, BS_PUSHBUTTON);

        myListView2->SetColumn("Nome", 180);
        myListView2->SetColumn("Sexo", 80);
        myListView2->SetColumn("Idade", 50);
        myListView2->SetColumn("Cargo", 130);
        myListView2->SetColumn("Salário", 80);
        myListView2->SetColumn("Data de Admissão", 120);

        showEmployee(*myListView2, 1);
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        int wmHId = HIWORD(wParam);

        // Limpa caixa de texto ao receber o foco
        if (HIWORD(wParam) == EN_SETFOCUS) {
            if (LOWORD(wParam) == ID_EDIT_NAME && addEmployeeEdit->GetText() == "Nome do Funcionário") {
                SetWindowText(addEmployeeEdit->hEdit, 0);
            }
            else if (LOWORD(wParam) == ID_EDIT_SEX && addEmployeeSexEdit->GetText() == "Sexo") {
                SetWindowText(addEmployeeSexEdit->hEdit, 0);
            }
            else if (LOWORD(wParam) == ID_EDIT_AGE && addEmployeeAgeEdit->GetText() == "Idade") {
                SetWindowText(addEmployeeAgeEdit->hEdit, 0);
            }
            else if (LOWORD(wParam) == ID_EDIT_JOB && addEmployeeJobEdit->GetText() == "Cargo") {
                SetWindowText(addEmployeeJobEdit->hEdit, 0);
            }
            else if (LOWORD(wParam) == ID_EDIT_SALARY && addEmployeeSalaryEdit->GetText() == "Salário") {
                SetWindowText(addEmployeeSalaryEdit->hEdit, 0);
            }
            else if (LOWORD(wParam) == ID_EDIT_ADMISSION && addEmployeeAdmissionEdit->GetText() == "Data de Admissão") {
                SetWindowText(addEmployeeAdmissionEdit->hEdit, 0);
            }
        }
        else if (HIWORD(wParam) == EN_KILLFOCUS) {
            if (LOWORD(wParam) == ID_EDIT_NAME && addEmployeeEdit->GetText() == "") {
                SetWindowText(addEmployeeEdit->hEdit, "Nome do Funcionário");
            }
            else if (LOWORD(wParam) == ID_EDIT_SEX && addEmployeeSexEdit->GetText() == "") {
                SetWindowText(addEmployeeSexEdit->hEdit, "Sexo");
            }
            else if (LOWORD(wParam) == ID_EDIT_AGE && addEmployeeAgeEdit->GetText() == "") {
                SetWindowText(addEmployeeAgeEdit->hEdit, "Idade");
            }
            else if (LOWORD(wParam) == ID_EDIT_JOB && addEmployeeJobEdit->GetText() == "") {
                SetWindowText(addEmployeeJobEdit->hEdit, "Cargo");
            }
            else if (LOWORD(wParam) == ID_EDIT_SALARY && addEmployeeSalaryEdit->GetText() == "") {
                SetWindowText(addEmployeeSalaryEdit->hEdit, "Salário");
            }
            else if (LOWORD(wParam) == ID_EDIT_ADMISSION && addEmployeeAdmissionEdit->GetText() == "") {
                SetWindowText(addEmployeeAdmissionEdit->hEdit, "Data de Admissão");
            }
        }

        switch (wmId)
        {
        case ID_ADDEMPLOYEE1:
        {
            // Adiciona novo empregado
            char resp;
            
            resp = addEmployeeFunction(hwnd, addEmployeeEdit->GetText(), addEmployeeSexEdit->GetText(),
                addEmployeeAgeEdit->GetText(), addEmployeeJobEdit->GetText(), addEmployeeSalaryEdit->GetText(), addEmployeeAdmissionEdit->GetText());
            if (resp == SQLITE_OK) {
                SetWindowText(addEmployeeEdit->hEdit, "Nome do Funcionário");
                SetWindowText(addEmployeeSexEdit->hEdit, "Sexo");
                SetWindowText(addEmployeeAgeEdit->hEdit, "Idade");
                SetWindowText(addEmployeeJobEdit->hEdit, "Cargo");
                SetWindowText(addEmployeeSalaryEdit->hEdit, "Salário");
                SetWindowText(addEmployeeAdmissionEdit->hEdit, "Data de Admissão");
                ListView_DeleteAllItems(myListView2->hListView); // Zera a ListView
                showEmployee(*myListView2, 1);
            }
        }
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
    }
    break;
    case WM_NOTIFY: {
        switch (((LPNMHDR)lParam)->code) {
        case TCN_SELCHANGE:
            ListView_DeleteAllItems(myListView2->hListView); // Zera a ListView
            if (myTab->getTabNumber() == 1) {
                showEmployee(*myListView2, 0);
            }
            else {
                showEmployee(*myListView2, 1);
            }
        }
        break;
    }
                  break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        DeleteDC(hdc);
        EndPaint(hwnd, &ps);
    }
    break;
    case WM_CTLCOLORSTATIC:
    {
        SetBkMode((HDC)wParam, TRANSPARENT);
        HBRUSH BGColorBrush = CreateSolidBrush(RGB(200, 200, 200));
        return (LRESULT)BGColorBrush;
        //return (LRESULT)GetStockObject(NULL_BRUSH);  // Ou nenhuma cor de fundo
    }
    break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}


/*--------------------------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProcPanelSale(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
    {                
        vendasTxtID = new Label(hwnd, ID_VENDASTXTMAX, " ", posX210, posY230, 95, 25);
        vendasTxtProduto = new Label(hwnd, ID_VENDASTXTPRODUCT, "Produto:", posX20, posY40, 300, 50);
        vendasTxtQuantidade = new Label(hwnd, ID_VENDASTXTQUANTITY, "Quantidade:", posX340, posY40, 100, 30);
        vendasTxtVendedor = new Label(hwnd, ID_VENDASTXTVENDOR, "Vendedor:", posX20, posY100, 300, 30);
        vendasTxtDate = new Label(hwnd, ID_VENDASTXTDATE, "Data:", posX340, posY100, 150, 30);
        vendasTxtPreco = new Label(hwnd, ID_VENDASTXTPRICE, "Preço:", posX20, posY160, 130, 40);
        vendasTxtTotal = new Label(hwnd, ID_VENDASTXTTOTAL, "Total:", posX340, posY160, 130, 40);
        showVendas(contadorVendas, *vendasTxtID, *vendasTxtProduto, *vendasTxtQuantidade, *vendasTxtVendedor, *vendasTxtDate, *vendasTxtPreco, *vendasTxtTotal);

        quadro1Img = (HBITMAP)LoadImage(NULL, "Resources\\Quadro1.bmp", IMAGE_BITMAP, 500, 330, LR_LOADFROMFILE);
        btnNextImg = (HBITMAP)LoadImage(NULL, "Resources\\BTNGreenProximo1.bmp", IMAGE_BITMAP, 104, 30, LR_LOADFROMFILE);
        btnPrevImg = (HBITMAP)LoadImage(NULL, "Resources\\BTNGreenAnterior1.bmp", IMAGE_BITMAP, 104, 30, LR_LOADFROMFILE);

        btnNext = new AnyButton(hwnd, ID_BTNNEXT, " ", posX270, posY270, 110, 34, BS_BITMAP | BS_CENTER);
        btnPrev = new AnyButton(hwnd, ID_BTNPREV, " ", posX140, posY270, 110, 34, BS_BITMAP | BS_CENTER);
        SendMessage(btnNext->hAnyButton, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)btnNextImg);
        SendMessage(btnPrev->hAnyButton, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)btnPrevImg);
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        int wmHId = HIWORD(wParam);
        switch (wmId)
        {
        case ID_BTNNEXT:
        {
            contadorVendas++;
            showVendas(contadorVendas, *vendasTxtID, *vendasTxtProduto, *vendasTxtQuantidade, *vendasTxtVendedor, *vendasTxtDate, *vendasTxtPreco, *vendasTxtTotal);
            ShowWindow(hwnd, 0);
            ShowWindow(hwnd, 1);
        }
        break;
        case ID_BTNPREV:
        {
            if (contadorVendas <= 2) {
                contadorVendas = 1;
            }
            else {
                contadorVendas--;
            }
            showVendas(contadorVendas, *vendasTxtID, *vendasTxtProduto, *vendasTxtQuantidade, *vendasTxtVendedor, *vendasTxtDate, *vendasTxtPreco, *vendasTxtTotal);
            ShowWindow(hwnd, 0);
            ShowWindow(hwnd, 1);
        }
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        HDC hdcImg;
        
        GetObject(quadro1Img, sizeof(BITMAP), &quadro1ImgBitMap); // Adiciona as propriedades da Imagem no bitmap

        hdcImg = CreateCompatibleDC(hdc); // cria um contexto de dispositivo para o bitmap
        SelectObject(hdcImg, quadro1Img);
        // Desenha o BitMap
        BitBlt(hdc, clientWindowCenterX - 250, clientWindowCenterY - 165, quadro1ImgBitMap.bmWidth, quadro1ImgBitMap.bmHeight, hdcImg, 0, 0, SRCCOPY);
        
        DeleteDC(hdc);
        DeleteDC(hdcImg);
        EndPaint(hwnd, &ps);
    }
    break;
    case WM_CTLCOLORSTATIC:
    {
        SetBkMode((HDC)wParam, TRANSPARENT);
        //HBRUSH BGColorBrush = CreateSolidBrush(RGB(200, 200, 200));
        //return (LRESULT)BGColorBrush;
        return (LRESULT)GetStockObject(NULL_BRUSH);  // Ou nenhuma cor de fundo
    }
    break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}


/*--------------------------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProcPanelConsult(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        myLabelMarca = new Label(hwnd, ID_LABEL5, "Marca: ", 10, 10, 70, 40);
        myLabelMarca->setFont("Arial", 25);
        myComboBox = new ComboBox(hwnd, ID_COMBOBOX1, "Marca", 90, 10, 120, 30);
        myComboBox->AddItem("Selecione...");
        myComboBox->AddItem("Kingston");
        myComboBox->AddItem("Logitech");
        myComboBox->SetInitialItem(0);

        productImgView = (HBITMAP)LoadImage(NULL, "Resources\\Search.bmp", IMAGE_BITMAP, 300, 300, LR_LOADFROMFILE);

        myListView = new ListView(hwnd, ID_LISTVIEW1, 10, 50, 600, 400);
        ListView_SetExtendedListViewStyle(myListView->hListView, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
        myListView->MakeTransparent();

        myListView->SetColumn("Produto", 180);
        myListView->SetColumn("Modelo", 140);
        myListView->SetColumn("Preço", 100);
        myListView->SetColumn("Garantia", 100);
        myListView->SetColumn("Dimenções", 140);
        myListView->SetColumn("Peso", 100);
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        int wmHId = HIWORD(wParam);
        switch (wmHId)
        {
        case CBN_SELCHANGE: // ComboBox mudou de item
            int ItemIndex;
            TCHAR  ListItem[25];
            ItemIndex = SendMessage(myComboBox->hComboBox, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
            (TCHAR)SendMessage(myComboBox->hComboBox, (UINT)CB_GETLBTEXT, (WPARAM)ItemIndex, (LPARAM)ListItem);
            comboStr.str("");
            comboStr << ListItem; // Adiciona o texto de TCHAR em uma String para comparação
            
            ListView_DeleteAllItems(myListView->hListView); // Zera a ListView
            productImgView = (HBITMAP)LoadImage(NULL, "Resources\\Search.bmp", IMAGE_BITMAP, 300, 300, LR_LOADFROMFILE);
            ShowWindow(hwnd, 0); // Atualiza a Imagem
            ShowWindow(hwnd, 1);

            if (comboStr.str() != "Selecione...")
            {
                if (comboStr.str() == "Kingston") {
                    showProduct(*myListView, "Kingston");
                }
                else if (comboStr.str() == "Logitech") {
                    showProduct(*myListView, "Logitech");
                }
            }
            
        }
    }
    break;
    case WM_NOTIFY: // the message that is being sent always
    {
        switch (LOWORD(wParam)) // hit Test para a ListView
        {
        case ID_LISTVIEW1:
        {
            // if code == NM_CLICK - Single click on an item
            if (((LPNMHDR)lParam)->code == NM_CLICK)
            {
                int ListViewIndex = myListView->GetSelectedItem();
                
                if (ListViewIndex != -1) // no items
                {
                    stringstream indexStr;
                    indexStr.str("");
                    if (comboStr.str() == "Kingston") {
                        // Mostra as imagens
                        switch (ListViewIndex) {
                        case 0:
                            indexStr << "Resources\\productsImg\\SSD Externo Portatil Kingston 1TB USB 3.2 Leitura 1.050MBs e Gravacao 1.050MBs - SXS10001000G IMG1.bmp";
                            break;
                        case 1:
                            indexStr << "Resources\\productsImg\\SSD Externo 1 TB Kingston XS2000 Leitura 2000 MBs e Gravacao 2000MBs - SXS20001000G IMG1.bmp";
                            break;
                        case 2:
                            indexStr << "Resources\\productsImg\\SSD Externo Portatil Kingston 2TB USB 3.2 Leitura 1.050MBs e Gravacao 1.050MBs - SXS10002000G IMG1.bmp";
                            break;
                        case 3:
                            indexStr << "Resources\\productsImg\\SSD Externo 2TB Kingston XS2000 Leitura 2000MBs e Gravacao 2000MBs - SXS20002000G IMG1.bmp";
                            break;
                        case 4:
                            indexStr << "Resources\\productsImg\\Pendrive 64GB Kingston USB 3.2 Datatraveler Exodia DTX64 Gen 1 IMG1.bmp";
                            break;
                        case 5:
                            indexStr << "Resources\\productsImg\\Pen Drive 64GB Kingston DataTraveler Exodia Onyx USB 3.2 - DTXON64GB IMG1.bmp";
                            break;
                        case 6:
                            indexStr << "Resources\\productsImg\\Pen Drive 16GB Kingston IronKey Keypad 200 USB Azul - IKKP200 16GB IMG1.bmp";
                            break;
                        case 7:
                            indexStr << "Resources\\productsImg\\Pen Drive 64GB Kingston IronKey Vault Privacy 50C USB-C Azul - IKVP50C 64GB IMG1.bmp";
                            break;
                        case 8:
                            indexStr << "Resources\\productsImg\\Memoria Kingston Fury Beast RGB 8GB 3200MHz DDR4 CL16 Preto - KF432C16BB2A8 IMG1.bmp";
                            break;
                        case 9:
                            indexStr << "Resources\\productsImg\\Memoria Kingston Fury Beast RGB 16GB 3200MHz DDR4 CL16 Preto - KF432C16BB12A16 IMG1.bmp";
                            break;
                        }
                    }
                    else if (comboStr.str() == "Logitech") {
                        // Mostra as imagens
                        switch (ListViewIndex) {
                        case 0:
                            indexStr << "Resources\\productsImg\\Teclado Sem Fio Logitech, Bluetooth e USB, Pebble Keys 2 K380s, Easy-Switch e Pilha Inclusa, Grafite IMG1.bmp";
                            break;
                        case 1:
                            indexStr << "Resources\\productsImg\\Mouse Sem Fio Logitech Pebble 2 M350s, USB Logi Bolt ou Bluetooth e Pilha Inclusa, com Clique Silencioso, Grafite IMG1.bmp";
                            break;
                        case 2:
                            indexStr << "Resources\\productsImg\\Teclado e Mouse sem fio Logitech MK295 com Digitacao e Clique Silencioso, Conexao USB, Pilhas Inclusas e Layout ABNT2 IMG1.bmp";
                            break;
                        case 3:
                            indexStr << "Resources\\productsImg\\Mouse sem fio Logitech Trackball MX Ergo com Ajuste de Angulo, USB Unifying ou Bluetooth e Bateria Recarregavel IMG1.bmp";
                            break;
                        case 4:
                            indexStr << "Resources\\productsImg\\Headset Sem Fio Logitech Zone Vibe 100, Drivers 40 mm, USB, Bluetooth, PC, Mobile, Grafite IMG1.bmp";
                            break;
                        }
                    }
                    // Mostra a imagem do produto na lateral
                    productImgView = (HBITMAP)LoadImage(NULL, indexStr.str().c_str(),IMAGE_BITMAP, 300, 300, LR_LOADFROMFILE);
                    
                    ShowWindow(hwnd, 0); // Atualiza a Imagem
                    ShowWindow(hwnd, 1);
                }
            }
        }
        break;
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        HDC hdcImg;
        GetObject(productImgView, sizeof(BITMAP), &productImgViewBitMap); // Adiciona as propriedades da Imagem no bitmap

        hdcImg = CreateCompatibleDC(hdc); // cria um contexto de dispositivo para o bitmap
        SelectObject(hdcImg, productImgView);
        // Desenha o BitMap
        BitBlt(hdc, productImgViewPosX, 50, productImgViewBitMap.bmWidth, productImgViewBitMap.bmHeight, hdcImg, 0, 0, SRCCOPY);
        
        DeleteDC(hdc);
        DeleteDC(hdcImg);
        EndPaint(hwnd, &ps);
    }
    break;
    case WM_CTLCOLORSTATIC:
    {
        SetBkMode((HDC)wParam, TRANSPARENT);
        HBRUSH BGColorBrush = CreateSolidBrush(RGB(200, 200, 200));
        return (LRESULT)BGColorBrush;
        //return (LRESULT)GetStockObject(NULL_BRUSH);  // Ou nenhuma cor de fundo
    }
    break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

/*--------------------------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProcPanel(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        introBG = (HBITMAP)LoadImage(NULL, "Resources\\IntroBG.bmp", IMAGE_BITMAP, mainWindowRec.right, mainWindowRec.bottom, LR_LOADFROMFILE);

        myLabel = new Label(hwnd, ID_LABEL1, "Informática", -240, 100, 240, 40, SS_RIGHT);
        myLabel2 = new Label(hwnd, ID_LABEL2, "Sistema da Loja", -240, 150, 240, 30, SS_RIGHT);
        myLabel3 = new Label(hwnd, ID_LABEL3, "Consulte:\nProdutos -\nVendas -\nFuncionários -"
            , 100, 200, 240, 130, SS_RIGHT);
        myLabel->setFont("Arial", 50);
        myLabel2->setFont("Times New Roman", 30);
        myLabel3->setFont("Gabriola", 35);
        ShowWindow(myLabel3->hLabel, 0); // Mostra o terceiro texto após o fim da animação

        timerCountMax = 85;
        addPosX = 4;
        addPosY = 0;
        addWidth = 0;
        addHeight = 0;

        SetTimer(hwnd, ID_TIMER_TRANSLATE, 20, NULL);
        return 0;
    }
    case WM_TIMER:
    {
        if (wParam == ID_TIMER_TRANSLATE) {
            translate(myLabel->hLabel, addPosX, addPosY, addWidth, addHeight);
            translate(myLabel2->hLabel, addPosX, addPosY, addWidth, addHeight);

            if (timerCount >= 84) { ShowWindow(myLabel3->hLabel, 1); }

            timerCount += 1;
            if (timerCount >= timerCountMax) {
                timerCount = 0;
                timerCountMax = 0;
                addPosX = 0;
                addPosY = 0;
                addWidth = 0;
                addHeight = 0;
                KillTimer(hwnd, ID_TIMER_TRANSLATE); // Pare o temporizador quando o contador chega ao máximo
            }
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        HDC hdcImg;
        GetObject(introBG, sizeof(BITMAP), &introBitMap); // Adiciona as propriedades da Imagem no bitmap

        hdcImg = CreateCompatibleDC(hdc); // cria um contexto de dispositivo para o bitmap
        SelectObject(hdcImg, introBG);
        // Desenha o BitMap
        BitBlt(hdc, 0, 0, introBitMap.bmWidth, introBitMap.bmHeight, hdcImg, 0, 0, SRCCOPY);

        DeleteDC(hdc);
        DeleteDC(hdcImg);
        EndPaint(hwnd, &ps);
    }
    break;
    case WM_CTLCOLORSTATIC:
    {
        SetBkMode((HDC)wParam, TRANSPARENT);
        HBRUSH BGColorBrush = CreateSolidBrush(RGB(255, 255, 255));  // Mesma cor da Janela
        return (LRESULT)BGColorBrush;
        //return (LRESULT)GetStockObject(NULL_BRUSH);  // Ou nenhuma cor de fundo
    }
    break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

/*--------------------------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProcPanelCalender(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    SYSTEMTIME systime;
    switch (msg)
    {
    case WM_CREATE:
    {
        calenderBG = (HBITMAP)LoadImage(NULL, "Resources\\CalendarioBG.bmp", IMAGE_BITMAP, mainWindowRec.right, mainWindowRec.bottom, LR_LOADFROMFILE);
        myMonthCalendar = new MonthCalendar(hwnd, ID_MONTHCALENDER, 45, 150, 450, 300);
        systime = myMonthCalendar->GetCurSel();

        stringstream dateStr;
        dateStr << systime.wYear;
        myLabel4 = new Label(hwnd, ID_LABEL4, dateStr.str().c_str(), mainWindowRec.right - 150, mainWindowRec.bottom - 100, 150, 75);
        myLabel4->setFont("Arial", 60);

        switch ((int)systime.wMonth) {
        case 1:
            monthImg = (HBITMAP)LoadImage(NULL, "Resources\\Janeiro.bmp", IMAGE_BITMAP, 130, 60, LR_LOADFROMFILE);
            break;
        case 2:
            monthImg = (HBITMAP)LoadImage(NULL, "Resources\\Fevereiro.bmp", IMAGE_BITMAP, 140, 60, LR_LOADFROMFILE);
            break;
        case 3:
            monthImg = (HBITMAP)LoadImage(NULL, "Resources\\Marco.bmp", IMAGE_BITMAP, 120, 60, LR_LOADFROMFILE);
            break;
        case 4:
            monthImg = (HBITMAP)LoadImage(NULL, "Resources\\Abril.bmp", IMAGE_BITMAP, 120, 60, LR_LOADFROMFILE);
            break;
        case 5:
            monthImg = (HBITMAP)LoadImage(NULL, "Resources\\Maio.bmp", IMAGE_BITMAP, 120, 60, LR_LOADFROMFILE);
            break;
        case 6:
            monthImg = (HBITMAP)LoadImage(NULL, "Resources\\Junho.bmp", IMAGE_BITMAP, 120, 60, LR_LOADFROMFILE);
            break;
        case 7:
            monthImg = (HBITMAP)LoadImage(NULL, "Resources\\Julho.bmp", IMAGE_BITMAP, 120, 60, LR_LOADFROMFILE);
            break;
        case 8:
            monthImg = (HBITMAP)LoadImage(NULL, "Resources\\Agosto.bmp", IMAGE_BITMAP, 120, 60, LR_LOADFROMFILE);
            break;
        case 9:
            monthImg = (HBITMAP)LoadImage(NULL, "Resources\\Setembro.bmp", IMAGE_BITMAP, 140, 60, LR_LOADFROMFILE);
            break;
        case 10:
            monthImg = (HBITMAP)LoadImage(NULL, "Resources\\Outubro.bmp", IMAGE_BITMAP, 140, 60, LR_LOADFROMFILE);
            break;
        case 11:
            monthImg = (HBITMAP)LoadImage(NULL, "Resources\\Novembro.bmp", IMAGE_BITMAP, 140, 60, LR_LOADFROMFILE);
            break;
        case 12:
            monthImg = (HBITMAP)LoadImage(NULL, "Resources\\Dezembro.bmp", IMAGE_BITMAP, 140, 60, LR_LOADFROMFILE);
            break;
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        HDC hdcImg;
        GetObject(calenderBG, sizeof(BITMAP), &calenderBitMap); // Adiciona as propriedades da Imagem no bitmap

        hdcImg = CreateCompatibleDC(hdc); // cria um contexto de dispositivo para o bitmap
        SelectObject(hdcImg, calenderBG);
        // Desenha o BitMap
        BitBlt(hdc, 0, 0, calenderBitMap.bmWidth, calenderBitMap.bmHeight, hdcImg, 0, 0, SRCCOPY);

        GetObject(monthImg, sizeof(BITMAP), &monthImgBitMap);
        SelectObject(hdcImg, monthImg);
        BitBlt(hdc, 50, 50, monthImgBitMap.bmWidth, monthImgBitMap.bmHeight, hdcImg, 0, 0, SRCCOPY);

        DeleteDC(hdc);
        DeleteDC(hdcImg);
        EndPaint(hwnd, &ps);
    }
    break;
    case WM_CTLCOLORSTATIC:
    {
        SetBkMode((HDC)wParam, TRANSPARENT);
        HBRUSH BGColorBrush = CreateSolidBrush(RGB(238, 27, 36));
        return (LRESULT)BGColorBrush;
        //return (LRESULT)GetStockObject(NULL_BRUSH);  // Ou nenhuma cor de fundo
    }
    break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

/*--------------------------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProcPanelContact(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg)
    {
    case WM_CREATE:
    {
        contactBG = (HBITMAP)LoadImage(NULL, "Resources\\ContatoBG.bmp", IMAGE_BITMAP, mainWindowRec.right, mainWindowRec.bottom, LR_LOADFROMFILE);
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        HDC hdcImg;
        hdcImg = CreateCompatibleDC(hdc);
        SelectObject(hdcImg, contactBG);
        GetObject(contactBG, sizeof(contactBitMap), &contactBitMap); // Adiciona as propriedades da Imagem no bitmap

        
        // Desenha o BitMap
        BitBlt(hdc, 0, 0, contactBitMap.bmWidth, contactBitMap.bmHeight, hdcImg, 0, 0, SRCCOPY);

        DeleteDC(hdc);
        DeleteDC(hdcImg);
        EndPaint(hwnd, &ps);
    }
    break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
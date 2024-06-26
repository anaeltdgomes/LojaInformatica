#ifndef BUTTON_H
#define BUTTON_H

class Button {
public:
    HWND hButton;

    Button(HWND parent, __int64 id, LPCSTR text, int x, int y, int width, int height) {
        hButton = CreateWindow("BUTTON", text,
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            x, y, width, height,
            parent, (HMENU)id, (HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE), NULL);
    }
    ~Button() { delete hButton; }

    void SetText(const char* texto) {
        SetWindowText(hButton, texto);
    }

    void setFont(LPCSTR fontName, int fontSize) {
        HFONT hFont = CreateFont(fontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
            OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
            VARIABLE_PITCH, fontName);
        SendMessage(hButton, WM_SETFONT, (WPARAM)hFont, TRUE);
    }
};

#endif
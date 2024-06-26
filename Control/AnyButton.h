#ifndef ANYBUTTON_H
#define ANYBUTTON_H

class AnyButton {
public:
    HWND hAnyButton;

    AnyButton(HWND parent, __int64 id, LPCSTR text, int x, int y, int width, int height, int styles) {
        hAnyButton = CreateWindow("BUTTON", text, WS_CHILD | WS_VISIBLE | styles, x, y, width, height,
            parent, (HMENU)id, (HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE), NULL);
    }
    ~AnyButton() { delete hAnyButton; }

    void SetText(const char* texto) {
        SetWindowText(hAnyButton, texto);
    }

    void setFont(LPCSTR fontName, int fontSize) {
        HFONT hFont = CreateFont(fontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
            OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
            VARIABLE_PITCH, fontName);
        SendMessage(hAnyButton, WM_SETFONT, (WPARAM)hFont, TRUE);
    }
};

#endif
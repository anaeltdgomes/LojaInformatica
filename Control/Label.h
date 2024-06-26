#ifndef LABEL_H
#define LABEL_H

class Label {
public:
    HWND hLabel;
    HWND hLabelFrame;

    Label(HWND parent, __int64 id, LPCSTR text, int x, int y, int width, int height, int style = 0) {
        hLabel = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", text,
            WS_VISIBLE | WS_CHILD | style,x, y, width, height,
            parent, (HMENU)id, (HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE), NULL);
        SetLayeredWindowAttributes(hLabel, 0, 0, LWA_COLORKEY);
    }
    ~Label() {
        delete hLabel;
        delete hLabelFrame;
    }

    void SetText(const char* texto) {
        SetWindowText(hLabel, texto);
    }

    void setFont(LPCSTR fontName, int fontSize) {
        HFONT hFont = CreateFont(fontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
            OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
            VARIABLE_PITCH, fontName);
        SendMessage(hLabel, WM_SETFONT, (WPARAM)hFont, TRUE);
    }

    void addLabelFrame(HWND parent, __int64 id, int x, int y, int width, int height) {
        hLabelFrame = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "",
            WS_CHILD | WS_GROUP | SS_BLACKFRAME | WS_VISIBLE, x, y, width, height,
            parent, (HMENU)id, (HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE), NULL);
        SetLayeredWindowAttributes(hLabel, 0, 0, LWA_COLORKEY);
    }
};

#endif
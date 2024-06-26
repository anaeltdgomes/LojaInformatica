#ifndef EDIT_H
#define EDIT_H

class Edit {
public:
    HWND hEdit;

    Edit(HWND parent, __int64 id, LPCSTR text, int x, int y, int width, int height) {
        hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", text,
            WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
            x, y, width, height,
            parent, (HMENU)id, (HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE), NULL);
    }
    ~Edit() { delete hEdit; }

    void SetText(const char* texto) {
        SetWindowText(hEdit, texto);
    }

    string GetText() {
        char buffer[256] = "";
        GetWindowText(hEdit, (LPSTR)buffer, 256);
        return buffer;
    }

    void setFont(LPCSTR fontName, int fontSize) {
        HFONT hFont = CreateFont(fontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
            OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
            VARIABLE_PITCH, fontName);
        SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
    }
};

#endif
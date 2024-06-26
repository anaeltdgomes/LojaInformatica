#ifndef COMBOBOX_H
#define COMBOBOX_H

class ComboBox{
public:
    HWND hComboBox;
    
    ComboBox(HWND parent, __int64 id, LPCSTR text, int x, int y, int width, int height) {
        hComboBox = CreateWindow(WC_COMBOBOX, TEXT(text),
            CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
            x, y, width, height,
            parent, (HMENU)id, (HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE), NULL);
    }
    
    ~ComboBox() { delete hComboBox; }

    void AddItem(const char* texto) {
        SendMessage(hComboBox, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)texto);
    }

    void SetInitialItem(int itemNum) {
        SendMessage(hComboBox, CB_SETCURSEL, (WPARAM)itemNum, (LPARAM)0);
    }

    string GetItem() {
        char buffer[256] = "";
        GetWindowText(hComboBox, (LPSTR)buffer, 256);
        return buffer;
    }
};

#endif
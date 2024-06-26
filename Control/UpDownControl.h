#ifndef UPDOWN_H
#define UPDOWN_H

class UpDownControl {
public:
    HWND hUpDown;

    UpDownControl(HWND parent, __int64 id, int x, int y, int width, int height, int styles) {
        hUpDown = CreateWindowEx(0, UPDOWN_CLASS, NULL, WS_CHILD | WS_VISIBLE | 
            UDS_ALIGNRIGHT | styles, x, y, width, height, parent, 
            (HMENU)id, (HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE), NULL);
    }
    ~UpDownControl() {
        delete hUpDown;
    }

    void SetRange(int minRange, int maxRange) {
        SendMessage(hUpDown, UDM_SETRANGE, 0, MAKELONG(maxRange, minRange));
    }

    int GetPosition() {
        return (int)SendMessage(hUpDown, UDM_GETPOS, 0, 0);
    }
};

#endif
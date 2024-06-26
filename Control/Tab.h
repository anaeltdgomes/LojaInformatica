#ifndef TAB_H
#define TAB_H

class TabControl {
public:
    HWND hTab;

    TabControl(HWND parent, __int64 id, int x, int y, int width, int height) {
        hTab = CreateWindowEx(0, WC_TABCONTROL, NULL, WS_CHILD | WS_VISIBLE,
            x, y, width, height, parent, (HMENU)id, (HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE), NULL);
    }
    ~TabControl() {
        delete hTab;
    }

    void AddTab(const char* tabText) {
        TCITEMW tie = { 0 };
        tie.mask = TCIF_TEXT; // ou TCIF_IMAGE
        tie.pszText = (LPWSTR)tabText;
        SendMessage(hTab, TCM_INSERTITEM, 0, (LPARAM)&tie);
    }

    int getTabNumber() {
        return TabCtrl_GetCurSel(hTab);
    }

    // --> Não é possível adicionar outros objetos dentro do Tab, por não ser um contêiner <--
    // Use as coordenadas do Tab como referência para mover outros objetos para
    // dentro dela através de, por exemplo, MoveWindow ou SetWindowPos
    // Caso a função não funcione use - TabCtrl_AdjustRect(HWND hwnd, Boolean bLarger, RECT prc);
    RECT getClientAreaInGroupBox(int padding = 0) {
        RECT rc;
        GetWindowRect(hTab, &rc);
        MapWindowPoints(0, hTab, (POINT*)&rc, 2);

        // Note that the top DUs should be 9 to completely avoid overlapping the
        // Tab text, but 8 is used instead for better alignment on a 4x4 design grid.
        RECT border = { 1, 8, 1, 1 };
        OffsetRect(&border, padding, padding);
        MapDialogRect(hTab, &border);

        // An extra padding in dialog(box) units can be specified (preferably in multiples of 4).
        rc.left += border.left;
        rc.right -= border.right;
        rc.top += border.top;
        rc.bottom -= border.bottom;

        return rc;
    }
};
#endif 
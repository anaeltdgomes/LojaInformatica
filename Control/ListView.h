#ifndef LISTVIEW_H
#define LISTVIEW_H

static int listViewColumnIndex = 0;

class ListView {
public:
    HWND hListView;
 
    ListView(HWND parent, __int64 id, int x, int y, int width, int height) {
        hListView = CreateWindow(WC_LISTVIEW, "", WS_CHILD | WS_VISIBLE | LVS_REPORT | WS_BORDER | LVS_EDITLABELS,
            x, y, width, height, parent, (HMENU)id, (HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE), NULL);
    }
    ~ListView() {
        delete hListView;
    }

    void SetColumn(const char* nome, int widht) {
        LVCOLUMN lvColumn = { 0 };
        lvColumn.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
        lvColumn.cx = widht;
        lvColumn.pszText = (LPSTR)nome;
        ListView_InsertColumn(hListView, listViewColumnIndex++, &lvColumn);
    }
    
    void SetRow(const char* nome,int row, int column) {
        LVITEM lvItem = { 0 };
        lvItem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
        lvItem.pszText = (LPSTR)nome;
        lvItem.iSubItem = 0;
        lvItem.state = 0;
        
        if (column == 0) 
        {
            lvItem.iItem = row;
            lvItem.iImage = row;
            ListView_InsertItem(hListView, &lvItem);
        }
        else 
        {
            lvItem.iItem = row;
            lvItem.iImage = row;
            ListView_SetItemText(hListView, row, column, (LPSTR)nome);
        }
    }

    void setFont(LPCSTR fontName, int fontSize) {
        HFONT hFont = CreateFont(fontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
            OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
            VARIABLE_PITCH, fontName);
        SendMessage(hListView, WM_SETFONT, (WPARAM)hFont, TRUE);
    }

    void MakeTransparent() {
        //to turn the listview transparent
        ListView_SetTextBkColor(hListView, CLR_NONE);
        ListView_SetBkColor(hListView, CLR_NONE);
    }

    int GetSelectedItem() {
        return SendMessage(hListView, LVM_GETNEXTITEM, -1, LVNI_FOCUSED); // return item selected
    }
};

#endif 
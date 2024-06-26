#ifndef IMAGELISTMANAGER_H
#define IMAGELISTMANAGER_H

class ImageListManager {
public:
    HIMAGELIST hImageList;

    ImageListManager(int cx, int cy, UINT flags, int cInitial, int cGrow) {
        hImageList = ImageList_Create(cx, cy, flags, cInitial, cGrow);
    }

    ~ImageListManager() {
        if (hImageList) {
            ImageList_Destroy(hImageList);
        }
    }

    int AddIcon(HICON hicon) {
        return ImageList_AddIcon(hImageList, hicon);
    }

    int AddIcon(const char* iconURL) {
        // Adiciona ícones à lista de imagens
        HICON hiconItem = (HICON)LoadImage(NULL, iconURL, IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
        return ImageList_AddIcon(hImageList, hiconItem);
    }
};

#endif 
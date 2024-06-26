#ifndef MONTHCALENDAR_H
#define MONTHCALENDAR_H

class MonthCalendar {
public:
    HWND hMonthCalendar;

    MonthCalendar(HWND parent, __int64 id, int x, int y, int width, int height) {
        hMonthCalendar = CreateWindowEx(0, MONTHCAL_CLASS, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | MCS_DAYSTATE,
            x, y, width, height, parent, (HMENU)id, (HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE), NULL);
    }
    ~MonthCalendar() {
        delete hMonthCalendar;
    }

    SYSTEMTIME GetCurSel() {
        SYSTEMTIME st;
        MonthCal_GetCurSel(hMonthCalendar, &st);
        return st;
    }

    void SetCurSel(const SYSTEMTIME& st) {
        MonthCal_SetCurSel(hMonthCalendar, &st);
    }
};

#endif 
#pragma once
class Later {
public:
 
    Later(int after, bool async, void (*task)(HWND), HWND hwnd) {

        // If async is true, start a new thread to execute the task after waiting for "after" milliseconds.
        if (async) {
            std::thread([after, task, hwnd]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(after));
                task(hwnd);
                }).detach();
        }
        else {
            // If async is false, wait for "after" milliseconds and execute the task.
            std::this_thread::sleep_for(std::chrono::milliseconds(after));
            task(hwnd);
        }
    }
    ~Later() {}
};
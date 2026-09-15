#include <iostream>
#include <windows.h>

BOOL WINAPI handler(DWORD signal) {
    if (signal == CTRL_C_EVENT) {
        std::cout << "You can't close me!\n";
        return TRUE;
    }
    return FALSE;
}

int main() {
    SetConsoleCtrlHandler(handler, TRUE);
    while (true) {
        std::cout << "Running...\n";
        Sleep(1000);
    }
    return 0;
}
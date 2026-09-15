#include <iostream>
#include <windows.h>

int main() {
    HANDLE process = GetCurrentProcess();
    if (SetPriorityClass(process, BELOW_NORMAL_PRIORITY_CLASS)) {
        std::cout << "Process priority changed successfully.\n";
    } else {
        std::cout << "Could not change process priority.\n";
    }
    return 0;
}
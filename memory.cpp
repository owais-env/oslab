#include <iostream>
#include <windows.h>

int main() {
    MEMORYSTATUSEX memory{};
    memory.dwLength = sizeof(memory);

    if (GlobalMemoryStatusEx(&memory)) {
        std::cout << "Total RAM: " << memory.ullTotalPhys / (1024 * 1024) << " MB\n";
        std::cout << "Available RAM: " << memory.ullAvailPhys / (1024 * 1024) << " MB\n";
    } else {
        std::cerr << "GlobalMemoryStatusEx failed with error: " << GetLastError() << "\n";
    }
    return 0;
}
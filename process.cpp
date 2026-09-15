#include <iostream>
#include <windows.h>

int main() {
    STARTUPINFOA si{};
    PROCESS_INFORMATION pi{};
    si.cb = sizeof(si);

    char command[] = "cmd.exe /C echo I am the child";

    if (CreateProcessA(nullptr, command, nullptr, nullptr, FALSE, 0,
                        nullptr, nullptr, &si, &pi)) {
        std::cout << "I am the parent\n";
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
    } else {
        std::cerr << "CreateProcess failed with error: " << GetLastError() << "\n";
    }
    return 0;
}
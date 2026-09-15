#include <iostream>
#include <windows.h>

int main() {
    STARTUPINFOA si{};
    PROCESS_INFORMATION pi{};
    si.cb = sizeof(si);

    char command[] = "cmd.exe /C ping 127.0.0.1 -n 3 >nul";

    if (CreateProcessA(nullptr, command, nullptr, nullptr, FALSE, 0,
                        nullptr, nullptr, &si, &pi)) {
        WaitForSingleObject(pi.hProcess, INFINITE);
        std::cout << "All done!\n";
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
    } else {
        std::cerr << "CreateProcess failed with error: " << GetLastError() << "\n";
    }
    return 0;
}
#include <iostream>
#include <windows.h>

int main() {
    HANDLE readPipe, writePipe;
    if (!CreatePipe(&readPipe, &writePipe, nullptr, 0)) {
        std::cerr << "CreatePipe failed with error: " << GetLastError() << "\n";
        return 1;
    }

    const char message[] = "Hello through the pipe!";
    DWORD written, bytesRead;
    char buffer[100] = {};

    WriteFile(writePipe, message, sizeof(message), &written, nullptr);
    ReadFile(readPipe, buffer, sizeof(buffer), &bytesRead, nullptr);

    std::cout << buffer << "\n";

    CloseHandle(readPipe);
    CloseHandle(writePipe);
    return 0;
}
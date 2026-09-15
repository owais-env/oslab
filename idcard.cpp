#include <iostream>
#include <windows.h>

int main() {
    std::cout << "My Process ID is: " << GetCurrentProcessId() << "\n";
    return 0;
}
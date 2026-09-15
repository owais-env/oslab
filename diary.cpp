#include <iostream>
#include <fstream>

int main() {
    std::ofstream file("diary.txt");
    if (!file) {
        std::cerr << "Failed to create diary.txt\n";
        return 1;
    }
    file << "Hello OS\n";
    file.close();
    std::cout << "diary.txt created and written successfully.\n";
    return 0;
}
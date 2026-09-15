#include <cstdio>

int main() {
    FILE* file = fopen("ghost.txt", "r");
    if (file == nullptr) {
        perror("Failed to open file");
        return 1;
    }
    fclose(file);
    return 0;
}
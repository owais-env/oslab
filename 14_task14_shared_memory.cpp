#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>

int main() {
    const char* name = "/shm_os_lab_cpp";
    const size_t SIZE = 1024;

    int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        return 1;
    }

    if (ftruncate(shm_fd, SIZE) == -1) {
        perror("ftruncate");
        return 1;
    }

    void* mapped = mmap(nullptr, SIZE, PROT_READ | PROT_WRITE,
                        MAP_SHARED, shm_fd, 0);

    if (mapped == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    char* ptr = static_cast<char*>(mapped);
    std::strcpy(ptr, "OS Shared Memory Payload");

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        sleep(1);
        std::cout << "Child read from SHM : " << ptr << '\n';
        munmap(mapped, SIZE);
        close(shm_fd);
        return 0;
    }

    waitpid(pid, nullptr, 0);

    munmap(mapped, SIZE);
    close(shm_fd);
    shm_unlink(name);

    return 0;
}

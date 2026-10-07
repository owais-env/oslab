#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "fork() failed\n";
        return 1;
    }

    if (pid == 0) {
        std::cout << "Child replacing its binary with 'ls -l'...\n";
        execlp("ls", "ls", "-l", (char*)nullptr);

        // This runs only if exec fails.
        perror("exec failed");
        _exit(1);
    }

    waitpid(pid, nullptr, 0);
    std::cout << "Parent reaped replaced child image\n";
    return 0;
}

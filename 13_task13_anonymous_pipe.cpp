#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

int main() {
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        close(fd[1]);

        char buffer[256] = {};
        ssize_t bytes = read(fd[0], buffer, sizeof(buffer) - 1);

        if (bytes > 0)
            std::cout << "Child read from pipe : " << buffer << '\n';

        close(fd[0]);
        return 0;
    }

    close(fd[0]);

    const char* message = "Hello Child from Kernel Pipe";
    write(fd[1], message, std::strlen(message) + 1);

    close(fd[1]);
    waitpid(pid, nullptr, 0);

    return 0;
}

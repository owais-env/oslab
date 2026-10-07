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
        std::cout << "Child PID : " << getpid() << " terminating now\n";
        _exit(0);
    }

    std::cout << "Parent sleeping for 10 s without wait(). Inspect with: ps -l\n";
    sleep(10);

    waitpid(pid, nullptr, 0);
    std::cout << "Parent cleaned up child. Exiting.\n";
    return 0;
}

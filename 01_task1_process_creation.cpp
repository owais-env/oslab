#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Process creation failed\n";
        return 1;
    } else if (pid == 0) {
        std::cout << "Child Process : PID = " << getpid()
                  << ", Parent PID = " << getppid() << '\n';
    } else {
        std::cout << "Parent Process : PID = " << getpid()
                  << ", Created Child PID = " << pid << '\n';
        wait(nullptr);
    }
    return 0;
}

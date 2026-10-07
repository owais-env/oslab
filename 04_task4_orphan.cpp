#include <iostream>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "fork() failed\n";
        return 1;
    }

    if (pid == 0) {
        std::cout << "Initial Parent PID : " << getppid() << '\n';
        sleep(3);
        std::cout << "After parent dies, new Parent PID : " << getppid() << '\n';
        return 0;
    }

    std::cout << "Parent PID : " << getpid() << " exiting immediately\n";
    return 0;
}

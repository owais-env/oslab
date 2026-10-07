#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int shared_counter = 100;

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "fork() failed\n";
        return 1;
    }

    if (pid == 0) {
        shared_counter += 50;
        std::cout << "Child sees shared_counter = " << shared_counter << '\n';
        _exit(0);
    }

    waitpid(pid, nullptr, 0);
    std::cout << "Parent sees shared_counter = " << shared_counter << '\n';
    return 0;
}

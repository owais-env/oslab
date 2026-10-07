#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "fork() failed\n";
        return 1;
    }

    if (pid == 0) {
        std::cout << "Child executing task ...\n";
        sleep(2);
        std::cout << "Child exiting with code 42\n";
        _exit(42);
    }

    std::cout << "Parent waiting for child ...\n";
    int status = 0;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status)) {
        std::cout << "Parent : Child terminated with exit status "
                  << WEXITSTATUS(status) << '\n';
    }
    return 0;
}

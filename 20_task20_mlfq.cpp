#include <iostream>
#include <queue>
#include <string>

struct Process {
    std::string pid;
    int remaining;
};

int main() {
    // Simple MLFQ demonstration based on the manual:
    // Q1 quantum = 2, Q2 quantum = 4, Q3 = FCFS.
    std::queue<Process> q1, q2, q3;

    q1.push({"P1", 7});
    q1.push({"P2", 1});

    int time = 0;

    while (!q1.empty() || !q2.empty() || !q3.empty()) {
        if (!q1.empty()) {
            Process p = q1.front();
            q1.pop();

            int run = std::min(2, p.remaining);
            std::cout << "Time " << time << ": " << p.pid
                      << " enters Q1 (runs " << run << " ms)";

            p.remaining -= run;
            time += run;

            if (p.remaining > 0) {
                std::cout << " -> Demoted to Q2\n";
                q2.push(p);
            } else {
                std::cout << " -> Terminated\n";
            }
        }
        else if (!q2.empty()) {
            Process p = q2.front();
            q2.pop();

            int run = std::min(4, p.remaining);
            std::cout << "Time " << time << ": " << p.pid
                      << " from Q2 runs (" << run << " ms)";

            p.remaining -= run;
            time += run;

            if (p.remaining > 0) {
                std::cout << " -> Demoted to Q3\n";
                q3.push(p);
            } else {
                std::cout << " -> Terminated\n";
            }
        }
        else if (!q3.empty()) {
            Process p = q3.front();
            q3.pop();

            std::cout << "Time " << time << ": " << p.pid
                      << " runs in Q3 until finished (" << p.remaining << " ms)\n";
            time += p.remaining;
            p.remaining = 0;
        }
    }

    std::cout << "All jobs completed.\n";
    return 0;
}

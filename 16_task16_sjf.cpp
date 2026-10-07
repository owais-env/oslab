#include <iostream>
#include <vector>
#include <iomanip>
#include <climits>

struct Process {
    std::string pid;
    int arrival, burst, completion = 0, turnaround = 0, waiting = 0;
    bool done = false;
};

int main() {
    // Values chosen to demonstrate the same order described in the manual.
    std::vector<Process> p = {
        {"P1", 0, 6},
        {"P2", 0, 8},
        {"P3", 0, 2}
    };

    int current = 0, completed = 0;
    double total_wait = 0;

    std::cout << "Execution Order : ";

    while (completed < static_cast<int>(p.size())) {
        int best = -1;

        for (int i = 0; i < static_cast<int>(p.size()); ++i) {
            if (!p[i].done && p[i].arrival <= current) {
                if (best == -1 || p[i].burst < p[best].burst)
                    best = i;
            }
        }

        if (best == -1) {
            ++current;
            continue;
        }

        Process& x = p[best];
        x.completion = current + x.burst;
        x.turnaround = x.completion - x.arrival;
        x.waiting = x.turnaround - x.burst;
        x.done = true;

        current = x.completion;
        total_wait += x.waiting;
        ++completed;

        std::cout << x.pid << (completed == p.size() ? "\n" : " -> ");
    }

    std::cout << "PID\tBurst\tWait Time\tTurnaround Time\n";
    for (const auto& x : p)
        std::cout << x.pid << '\t' << x.burst << '\t'
                  << x.waiting << "\t\t" << x.turnaround << '\n';

    std::cout << std::fixed << std::setprecision(2)
              << "Average Waiting Time : " << total_wait / p.size() << " ms\n";

    return 0;
}

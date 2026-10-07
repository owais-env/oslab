#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

struct Process {
    std::string pid;
    int arrival, burst, completion = 0, turnaround = 0, waiting = 0;
};

int main() {
    std::vector<Process> p = {
        {"P1", 0, 5},
        {"P2", 1, 3},
        {"P3", 2, 8}
    };

    std::sort(p.begin(), p.end(), [](const Process& a, const Process& b) {
        return a.arrival < b.arrival;
    });

    int current = 0;
    double total_wait = 0;

    for (auto& x : p) {
        if (current < x.arrival)
            current = x.arrival;

        x.completion = current + x.burst;
        x.turnaround = x.completion - x.arrival;
        x.waiting = x.turnaround - x.burst;
        current = x.completion;
        total_wait += x.waiting;
    }

    std::cout << "PID\tArrival\tBurst\tCompletion\tTurnaround\tWait\n";
    for (const auto& x : p)
        std::cout << x.pid << '\t' << x.arrival << '\t' << x.burst << '\t'
                  << x.completion << "\t\t" << x.turnaround << '\t\t'
                  << x.waiting << '\n';

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average Waiting Time : " << total_wait / p.size() << " ms\n";

    return 0;
}

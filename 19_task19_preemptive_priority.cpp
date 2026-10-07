#include <iostream>
#include <vector>

struct Process {
    std::string pid;
    int priority, burst, arrival, remaining, completion = 0, waiting = 0;
};

int main() {
    // Lower number means higher priority, as stated in the manual.
    std::vector<Process> p = {
        {"P1", 2, 4, 0, 4},
        {"P2", 1, 3, 1, 3},
        {"P3", 3, 2, 2, 2}
    };

    int current = 0, completed = 0;

    while (completed < static_cast<int>(p.size())) {
        int best = -1;

        for (int i = 0; i < static_cast<int>(p.size()); ++i) {
            if (p[i].arrival <= current && p[i].remaining > 0) {
                if (best == -1 || p[i].priority < p[best].priority)
                    best = i;
            }
        }

        if (best == -1) {
            ++current;
            continue;
        }

        --p[best].remaining;
        ++current;

        if (p[best].remaining == 0) {
            p[best].completion = current;
            p[best].waiting = p[best].completion
                            - p[best].arrival - p[best].burst;
            ++completed;
        }
    }

    std::cout << "PID\tPriority\tBurst\tArrival\tWaiting Time\n";
    for (const auto& x : p)
        std::cout << x.pid << '\t' << x.priority << "\t\t"
                  << x.burst << '\t' << x.arrival << '\t'
                  << x.waiting << '\n';

    return 0;
}

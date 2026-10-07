#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

struct Process {
    std::string pid;
    int arrival, burst, remaining, completion = 0, waiting = 0;
};

int main() {
    std::vector<Process> p = {
        {"P1", 0, 10, 10},
        {"P2", 1, 4, 4},
        {"P3", 5, 2, 2}
    };

    int current = 0, completed = 0;
    std::string last = "";
    int segment_start = 0;

    std::cout << "Timeline: ";

    while (completed < static_cast<int>(p.size())) {
        int best = -1;

        for (int i = 0; i < static_cast<int>(p.size()); ++i) {
            if (p[i].arrival <= current && p[i].remaining > 0) {
                if (best == -1 || p[i].remaining < p[best].remaining)
                    best = i;
            }
        }

        if (best == -1) {
            ++current;
            continue;
        }

        if (last != p[best].pid) {
            if (!last.empty())
                std::cout << "[" << last << " : " << segment_start
                          << "-" << current << "] ";
            last = p[best].pid;
            segment_start = current;
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

    if (!last.empty())
        std::cout << "[" << last << " : " << segment_start << "-" << current << "]\n";

    std::cout << "PID\tCompletion\tWaiting Time\n";
    for (const auto& x : p)
        std::cout << x.pid << '\t' << x.completion << "\t\t"
                  << x.waiting << '\n';

    return 0;
}

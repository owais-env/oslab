#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

struct Process {
    std::string pid;
    int arrival, burst, remaining, completion = 0, waiting = 0, turnaround = 0;
};

int main() {
    int quantum = 2;

    std::vector<Process> p = {
        {"P1", 0, 3, 3},
        {"P2", 0, 4, 4},
        {"P3", 0, 4, 4}
    };

    std::queue<int> q;
    int current = 0, completed = 0;

    for (int i = 0; i < static_cast<int>(p.size()); ++i)
        if (p[i].arrival <= current) q.push(i);

    std::cout << "Quantum = " << quantum << "\nExecution : ";

    while (completed < static_cast<int>(p.size())) {
        if (q.empty()) {
            ++current;
            for (int i = 0; i < static_cast<int>(p.size()); ++i)
                if (p[i].arrival <= current && p[i].remaining > 0)
                    q.push(i);
            continue;
        }

        int i = q.front();
        q.pop();

        int slice = std::min(quantum, p[i].remaining);
        std::cout << p[i].pid << " (" << slice << " ms) -> ";

        p[i].remaining -= slice;
        current += slice;

        for (int j = 0; j < static_cast<int>(p.size()); ++j) {
            if (p[j].arrival <= current && p[j].remaining > 0) {
                bool already = false;
                std::queue<int> temp = q;
                while (!temp.empty()) {
                    if (temp.front() == j) already = true;
                    temp.pop();
                }
                if (!already && j != i) q.push(j);
            }
        }

        if (p[i].remaining > 0) {
            q.push(i);
        } else {
            p[i].completion = current;
            p[i].turnaround = p[i].completion - p[i].arrival;
            p[i].waiting = p[i].turnaround - p[i].burst;
            ++completed;
        }
    }

    std::cout << "\nPID\tTurnaround\tWait\n";
    for (const auto& x : p)
        std::cout << x.pid << '\t' << x.turnaround << "\t\t" << x.waiting << '\n';

    return 0;
}

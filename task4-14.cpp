#include <iostream>
#include <thread>
#include <latch>
#include <vector>
using namespace std;

int main() {
    const int workers = 4;
    latch start_flag(1);

    auto worker = [&](int id) {
        cout << "Worker " << id << " is waiting.\n";
        start_flag.wait();
        cout << "Worker " << id << " started benchmark.\n";
    };

    vector<thread> threads;
    for (int i = 1; i <= workers; ++i)
        threads.emplace_back(worker, i);

    cout << "Main thread prepares shared resources...\n";
    start_flag.count_down();

    for (auto& t : threads)
        t.join();

    return 0;
}

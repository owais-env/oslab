#include <iostream>
#include <thread>
#include <barrier>
#include <vector>
#include <chrono>
using namespace std;

int main() {
    const int num_threads = 4;
    barrier sync_point(num_threads);

    auto worker = [&](int id) {
        cout << "Thread " << id << " completed Phase 1.\n";
        this_thread::sleep_for(chrono::milliseconds(100 * id));
        sync_point.arrive_and_wait();

        cout << "Thread " << id << " started Phase 2.\n";
    };

    vector<thread> threads;
    for (int i = 1; i <= num_threads; ++i)
        threads.emplace_back(worker, i);

    for (auto& t : threads)
        t.join();

    return 0;
}

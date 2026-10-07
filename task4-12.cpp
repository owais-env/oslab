#include <iostream>
#include <thread>
#include <semaphore>
#include <vector>
#include <chrono>
using namespace std;

counting_semaphore<3> sem(3);

void task(int id) {
    sem.acquire();
    cout << "Thread " << id << " entered the limited resource.\n";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "Thread " << id << " leaving the resource.\n";
    sem.release();
}

int main() {
    vector<thread> threads;
    for (int i = 1; i <= 6; ++i)
        threads.emplace_back(task, i);

    for (auto& t : threads)
        t.join();

    cout << "At most 3 threads used the resource at one time.\n";
    return 0;
}

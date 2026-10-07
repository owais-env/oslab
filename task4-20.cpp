#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <algorithm>
using namespace std;

const int N = 5;
mutex forks[N];

void dine(int id) {
    int left = id;
    int right = (id + 1) % N;

    int first = min(left, right);
    int second = max(left, right);

    {
        unique_lock<mutex> l1(forks[first]);
        unique_lock<mutex> l2(forks[second]);

        cout << "Philosopher " << id << " is eating.\n";
        this_thread::sleep_for(chrono::milliseconds(300));
    }

    cout << "Philosopher " << id << " finished eating.\n";
}

int main() {
    vector<thread> philosophers;

    for (int i = 0; i < N; ++i)
        philosophers.emplace_back(dine, i);

    for (auto& t : philosophers)
        t.join();

    cout << "Dining philosophers completed using resource hierarchy.\n";
    return 0;
}

#include <iostream>
#include <thread>
#include <vector>
using namespace std;

thread_local int txn_id = 0;

void run(int id) {
    txn_id++;
    cout << "Thread " << id << " has private txn_id = " << txn_id << '\n';
}

int main() {
    vector<thread> threads;
    for (int i = 1; i <= 4; ++i)
        threads.emplace_back(run, i);

    for (auto& t : threads)
        t.join();

    return 0;
}

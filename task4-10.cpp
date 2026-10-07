#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

mutex mtxA, mtxB;

void transfer1() {
    scoped_lock lock(mtxA, mtxB);
    cout << "Thread 1 safely acquired both locks.\n";
}

void transfer2() {
    scoped_lock lock(mtxB, mtxA);
    cout << "Thread 2 safely acquired both locks.\n";
}

int main() {
    thread t1(transfer1), t2(transfer2);
    t1.join();
    t2.join();
    cout << "Both transfers completed without deadlock.\n";
    return 0;
}

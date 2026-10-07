#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

mutex mtxA, mtxB;

void thread1() {
    lock_guard<mutex> lockA(mtxA);
    cout << "Thread 1 acquired Lock A.\n";
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "Thread 1 is waiting for Lock B.\n";
    lock_guard<mutex> lockB(mtxB);
    cout << "Thread 1 acquired Lock B.\n";
}

void thread2() {
    lock_guard<mutex> lockB(mtxB);
    cout << "Thread 2 acquired Lock B.\n";
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "Thread 2 is waiting for Lock A.\n";
    lock_guard<mutex> lockA(mtxA);
    cout << "Thread 2 acquired Lock A.\n";
}

int main() {
    cout << "Deadlock demonstration. The program intentionally waits forever.\n";
    thread t1(thread1), t2(thread2);
    t1.join();
    t2.join();
    return 0;
}

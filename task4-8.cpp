#include <iostream>
#include <thread>
#include <shared_mutex>
#include <vector>
using namespace std;

int data_value = 100;
shared_mutex rw_mtx;

void reader(int id) {
    shared_lock<shared_mutex> lock(rw_mtx);
    cout << "Reader " << id << " reads value: " << data_value << '\n';
}

void writer(int value) {
    unique_lock<shared_mutex> lock(rw_mtx);
    data_value = value;
    cout << "Writer changed value to: " << data_value << '\n';
}

int main() {
    thread r1(reader, 1), r2(reader, 2);
    r1.join();
    r2.join();

    thread w(writer, 200);
    w.join();

    thread r3(reader, 3);
    r3.join();
    return 0;
}

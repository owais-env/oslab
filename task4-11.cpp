#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>
using namespace std;

queue<int> q;
mutex mtx;
condition_variable cv;
bool finished = false;

void producer() {
    for (int i = 1; i <= 5; ++i) {
        {
            lock_guard<mutex> lock(mtx);
            q.push(i);
            cout << "Produced: " << i << '\n';
        }
        cv.notify_one();
        this_thread::sleep_for(chrono::milliseconds(200));
    }
    {
        lock_guard<mutex> lock(mtx);
        finished = true;
    }
    cv.notify_one();
}

void consumer() {
    while (true) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return !q.empty() || finished; });

        if (q.empty() && finished)
            break;

        int item = q.front();
        q.pop();
        lock.unlock();

        cout << "Consumed: " << item << '\n';
    }
}

int main() {
    thread p(producer), c(consumer);
    p.join();
    c.join();
    return 0;
}

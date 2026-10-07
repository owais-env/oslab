#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <vector>
using namespace std;

class ThreadPool {
    queue<function<void()>> tasks;
    mutex queue_mtx;
    condition_variable cv;
    bool stop = false;
    vector<thread> workers;

public:
    ThreadPool(int count) {
        for (int i = 0; i < count; ++i) {
            workers.emplace_back([this]() {
                while (true) {
                    function<void()> task;
                    {
                        unique_lock<mutex> lock(queue_mtx);
                        cv.wait(lock, [this] { return stop || !tasks.empty(); });
                        if (stop && tasks.empty())
                            return;
                        task = move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    void add(function<void()> task) {
        {
            lock_guard<mutex> lock(queue_mtx);
            tasks.push(move(task));
        }
        cv.notify_one();
    }

    ~ThreadPool() {
        {
            lock_guard<mutex> lock(queue_mtx);
            stop = true;
        }
        cv.notify_all();
        for (auto& t : workers)
            t.join();
    }
};

int main() {
    ThreadPool pool(3);

    for (int i = 1; i <= 6; ++i) {
        pool.add([i]() {
            cout << "Worker executed task " << i << '\n';
        });
    }

    return 0;
}

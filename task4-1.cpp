#include <iostream>
#include <thread>
using namespace std;

void child_routine() {
    cout << "Child thread executing. Thread ID: " << this_thread::get_id() << '\n';
}

int main() {
    thread t(child_routine);
    t.join();
    cout << "Main thread: child thread has finished.\n";
    return 0;
}

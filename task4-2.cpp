#include <iostream>
#include <thread>
#include <functional>
using namespace std;

void worker(int val, int& ref) {
    val += 10;
    ref += 10;
    cout << "Inside thread - value copy: " << val << '\n';
    cout << "Inside thread - reference value: " << ref << '\n';
}

int main() {
    int x = 5, y = 5;
    thread t(worker, x, ref(y));
    t.join();

    cout << "Main thread - x (passed by value): " << x << '\n';
    cout << "Main thread - y (passed by reference): " << y << '\n';
    return 0;
}

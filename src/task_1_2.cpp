#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void Thread1() {
    cout << "1 (from detached thread 1)\n";
}

void Thread2() {
    cout << "2 (from detached thread 2)\n";
}

int main() {
    thread t1(Thread1);
    thread t2(Thread2);

    t1.detach();
    t2.detach();

    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "Main finished." << endl;
    return 0;
}

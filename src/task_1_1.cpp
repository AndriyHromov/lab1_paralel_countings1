#include <iostream>
#include <thread>

using namespace std;

void Thread1() {
    cout << "1 ";
}

void Thread2() {
    cout << "2 ";
}

int main() {
    thread t1(Thread1);
    thread t2(Thread2);

    t1.join();
    t2.join();

    cout << "\nMain finished." << endl;
    return 0;
}

#include <iostream>
#include <thread>
#include <list>
#include <mutex>
#include <chrono>

using namespace std;

list<int> l;
mutex mtx;

void AddToList(int val) {
    for (int i = 0; i < 10; ++i) {
        mtx.lock();
        l.push_back(val + i);
        cout << "Added: " << (val + i) << endl;
        mtx.unlock();
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

void ListContains(int val) {
    for (int i = 0; i < 10; ++i) {
        mtx.lock();
        bool found = false;
        for (int elem : l) {
            if (elem == val) {
                found = true;
                break;
            }
        }
        if (found)
            cout << "Element " << val << " found.\n";
        else
            cout << "Element " << val << " NOT found.\n";
        mtx.unlock();
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

int main() {
    int targetVal = 5;
    thread t1(AddToList, targetVal);
    thread t2(ListContains, targetVal);

    t1.join();
    t2.join();

    return 0;
}

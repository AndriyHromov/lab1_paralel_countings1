#include <iostream>
#include <thread>
#include <list>
#include <mutex>
#include <chrono>

using namespace std;

list<int> l;
mutex mtx;

void AddToList(int val) {
    lock_guard<mutex> guard(mtx);
    l.push_back(val);
    cout << "Added once: " << val << endl;
}

void ListContains(int val) {
    lock_guard<mutex> guard(mtx);
    bool found = false;
    for (int elem : l) {
        if (elem == val) {
            found = true;
            break;
        }
    }
    if (found)
        cout << "Checked: Element " << val << " found.\n";
    else
        cout << "Checked: Element " << val << " NOT found.\n";
}

int main() {
    int baseVal = 100;
    int searchVal = 105;

    for (int i = 0; i < 10; ++i) {
        thread t1(AddToList, baseVal + i);
        thread t2(ListContains, searchVal);

        t1.detach();
        t2.detach();
    }

    this_thread::sleep_for(chrono::milliseconds(100));
    return 0;
}

#include <iostream>
#include <thread>
#include <list>
#include <chrono>

using namespace std;

list<int> l;

void AddToList(int val) {
    for (int i = 0; i < 10; ++i) {
        l.push_back(val + i);
        cout << "Added: " << (val + i) << endl;
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

void ListContains(int val) {
    for (int i = 0; i < 10; ++i) {
        bool found = false;
        for (auto it = l.begin(); it != l.end(); ++it) {
            if (*it == val) {
                found = true;
                break;
            }
        }
        if (found)
            cout << "Element " << val << " found in list.\n";
        else
            cout << "Element " << val << " NOT found in list.\n";
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

int main() {
    int targetVal = 5;
    thread t1(AddToList, targetVal);
    thread t2(ListContains, targetVal);

    t1.join();
    t2.join();

    cout << "Final list size: " << l.size() << endl;
    return 0;
}

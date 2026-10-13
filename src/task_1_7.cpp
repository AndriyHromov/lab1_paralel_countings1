#include <iostream>
#include <string>
#-include <thread> // (залиште звичайний include thread)
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

struct SomeData {
    string name;
    string surname;
    string address;
    int age;

    void print(const string& prefix) const {
        cout << prefix << " -> Name: " << name << ", Surname: " << surname 
             << ", Address: " << address << ", Age: " << age << endl;
    }
};

class ExchangePerson {
private:
    SomeData data;
    mutable mutex mtx;

public:
    ExchangePerson(string n, string s, string a, int ag) : data{n, s, a, ag} {}

    SomeData& getData() { return data; }
    mutex& getMutex() { return mtx; }

    static void JohnDoe(ExchangePerson& person) {
        lock_guard<mutex> guard(person.mtx);
        person.data.name = "John";
        person.data.surname = "Doe";
        person.data.address = "Unknown";
        person.data.age = 120;
    }

    static void JacobSmith(ExchangePerson& person) {
        lock_guard<mutex> guard(person.mtx);
        person.data.name = "Jacob";
        person.data.surname = "Smith";
        person.data.address     = "Known";
        person.data.age = 1;
    }

    // Завдання 1.7: Варіант функції Swap з unique_lock та defer_lock
    static void Swap(ExchangePerson& p1, ExchangePerson& p2) {
        if (&p1 == &p2) return;

        unique_lock<mutex> lock1(p1.mtx, defer_lock);
        unique_lock<mutex> lock2(p2.mtx, defer_lock);

        std::lock(lock1, lock2);

        SomeData temp = p1.data;
        p1.data = p2.data;
        p2.data = temp;
    }
};

int main() {
    ExchangePerson p1("Alice", "Brown", "Kyiv", 25);
    ExchangePerson p2("Bob", "Green", "Lviv", 30);

    thread tSwap(ExchangePerson::Swap, ref(p1), ref(p2));
    tSwap.join();

    p1.getData().print("Person 1 after Swap (unique_lock)");
    return 0;
}

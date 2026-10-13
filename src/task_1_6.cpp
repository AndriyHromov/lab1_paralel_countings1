#include <iostream>
#include <string>
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
        person.data.address = "Known";
        person.data.age = 1;
    }

    static void Swap(ExchangePerson& p1, ExchangePerson& p2) {
        if (&p1 == &p2) return;

        std::lock(p1.mtx, p2.mtx);

        lock_guard<mutex> guard1(p1.mtx, adopt_lock);
        lock_guard<mutex> guard2(p2.mtx, adopt_lock);

        SomeData temp = p1.data;
        p1.data = p2.data;
        p2.data = temp;
    }
};

int main() {
    ExchangePerson p1("Alice", "Brown", "Kyiv", 25);
    ExchangePerson p2("Bob", "Green", "Lviv", 30);

    cout << "--- BEFORE SWAP ---" << endl;
    p1.getData().print("Person 1");
    p2.getData().print("Person 2");

    thread t1(ExchangePerson::JohnDoe, ref(p1));
    thread t2(ExchangePerson::JacobSmith, ref(p2));
    t1.detach();
    t2.detach();

    this_thread::sleep_for(chrono::milliseconds(50));

    cout << "\n--- AFTER INDIVIDUAL THREADS ---" << endl;
    p1.getData().print("Person 1");
    p2.getData().print("Person 2");

    thread tSwap(ExchangePerson::Swap, ref(p1), ref(p2));
    tSwap.join();

    cout << "\n--- AFTER SWAP ---" << endl;
    p1.getData().print("Person 1");
    p2.getData().print("Person 2");

    return 0;
}

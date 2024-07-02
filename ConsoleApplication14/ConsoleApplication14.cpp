#include <iostream>

using namespace std;

class Person {
private:
    char* name;
    int age;
public:
    Person(const char* n, int a) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        age = a;
    }

    Person(const Person& p) {
        name = new char[strlen(p.name) + 1];
        strcpy(name, p.name);
        age = p.age;
    }

    ~Person() {
        delete[] name;
    }

    void printInfo() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

class Apartment {
private:
    Person** tenants;
    int numTenants;
    int capacity;
public:
    Apartment(int cap) {
        capacity = cap;
        tenants = new Person * [capacity];
        numTenants = 0;
    }

    Apartment(const Apartment& a) {
        capacity = a.capacity;
        tenants = new Person * [capacity];
        numTenants = a.numTenants;
        for (int i = 0; i < numTenants; i++) {
            tenants[i] = new Person(*a.tenants[i]);
        }
    }

    ~Apartment() {
        for (int i = 0; i < numTenants; i++) {
            delete tenants[i];
        }
        delete[] tenants;
    }

    void addTenant(Person* p) {
        if (numTenants < capacity) {
            tenants[numTenants] = p;
            numTenants++;
        }
    }

    void printTenants() {
        for (int i = 0; i < numTenants; i++) {
            tenants[i]->printInfo();
        }
    }
};

class Building {
private:
    Apartment** apartments;
    int numApartments;
    int capacity;
public:
    Building(int cap) {
        capacity = cap;
        apartments = new Apartment * [capacity];
        numApartments = 0;
    }

    Building(const Building& b) {
        capacity = b.capacity;
        apartments = new Apartment * [capacity];
        numApartments = b.numApartments;
        for (int i = 0; i < numApartments; i++) {
            apartments[i] = new Apartment(*b.apartments[i]);
        }
    }

    ~Building() {
        for (int i = 0; i < numApartments; i++) {
            delete apartments[i];
        }
        delete[] apartments;
    }

    void addApartment(Apartment* a) {
        if (numApartments < capacity) {
            apartments[numApartments] = a;
            numApartments++;
        }
    }

    void printApartments() {
        for (int i = 0; i < numApartments; i++) {
            cout << "Apartment " << i + 1 << ":" << endl;
            apartments[i]->printTenants();
        }
    }
};

int main() {
    Building house(2);

    Person p1("John Doe", 30);
    Person p2("Jane Doe", 25);
    Person p3("Mike Smith", 35);

    Apartment a1(3);
    a1.addTenant(&p1);
    a1.addTenant(&p2);

    Apartment a2(2);
    a2.addTenant(&p3);

    house.addApartment(&a1);
    house.addApartment(&a2);

    house.printApartments();

    return 0;
}
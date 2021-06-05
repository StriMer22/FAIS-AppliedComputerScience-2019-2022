#include<iostream>
#include <vector>

class set {
    std::vector<int> vec;
public:

    int getSize();

    void printSet();

    void insert(int x);

    void withdraw(int x);

    bool isInSet(int x);

    set operator+(set &obj);

    set operator*(set &obj);

    set operator-(set &obj);

    bool operator==(set &obj);

    bool operator<=(set &obj);

};



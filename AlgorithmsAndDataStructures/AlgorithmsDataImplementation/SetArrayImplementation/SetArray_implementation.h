//
// Created by Dmytro on 12.03.2021.
//

#include <iostream>

class setArr {
    int size;
    const int universeSize = 100;
    int *table;

    bool checkRangeCorrectness(int x);

public:
    setArr();

    void insert(int x);

    void withdraw(int x);

    bool isInSet(int i);

    int getSize() const;

    void clearSet();

    void printSet();

    setArr operator+(setArr &object);

    setArr operator*(setArr &object);

    setArr operator-(setArr &object);

    bool operator==(setArr &object);

    bool operator<=(setArr &object);
};

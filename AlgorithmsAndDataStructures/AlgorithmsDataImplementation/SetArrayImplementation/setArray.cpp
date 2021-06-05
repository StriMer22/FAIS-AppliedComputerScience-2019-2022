// CppSet.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SetArray_implementation.cpp"


int main() {
    std::cout << "Set testy\n***\n";

    setArr X = setArr();
    std::cout << X.isInSet(10) << "\n";
    X.insert(10);
    std::cout << X.isInSet(10) << "\n";

    X.insert(50);
    X.insert(11);
    X.insert(11);
    X.insert(2);
    X.insert(3);
    std::cout << "set size  " << X.getSize();

    std::cout << "\nSet X    ";
    X.printSet();

    setArr Y = setArr();
    Y.insert(1);
    Y.insert(2);
    Y.insert(5);
    std::cout << "Set Y    ";
    Y.printSet();

    std::cout << "Sum of sets\n";
    setArr Z = X + Y;
    std::cout << "Set Z    ";
    Z.printSet();

    std::cout << "Intersection of sets\n";
    setArr Z1 = X * Y;
    std::cout << "Set Z1    ";
    Z1.printSet();

    std::cout << "Difference of sets\n";
    setArr Z2 = X - Y;
    std::cout << "Set Z2    ";
    Z2.printSet();

    std::cout << "\n\nTest dodania zbyt duzej liczby\n";
    X.insert(111);


    std::cout << "\n\n\nTest porownywania/zawierania zbiorow\n";
    setArr C = setArr();
    C.insert(1);
    C.insert(2);
    C.insert(4);
    setArr D = setArr();
    D.insert(1);
    D.insert(2);
    D.insert(4);
    D.insert(7);


    std::cout << (bool) (C <= D) << "\n";
    std::cout << (bool) (D <= C) << "\n";
    std::cout << (bool) (C == C) << "\n";
}

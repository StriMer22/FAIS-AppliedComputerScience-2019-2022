//
// Created by homen on 21.03.2021.
//

#include "setList.h"
#include <iostream>
#include <algorithm>

int set::getSize() {
    return vec.size();
}

void set::printSet() {
    for (int i : vec) {
        std::cout << i << ' ';
    }
    std::cout << "\n";
}

void set::insert(int x) {
    if (!isInSet(x)) {
        vec.push_back(x);
    }
}

bool set::isInSet(int x) {
    return (std::find(vec.begin(), vec.end(), x) != vec.end());
}

void set::withdraw(int x) {
    if (isInSet(x)) {
        vec.erase(std::remove(vec.begin(), vec.end(), x), vec.end());
    } else {
        std::cout << "Element not found in Set";
    }
}

set set::operator+(set &obj) {
    set tempo;
    for (auto i : vec) {
        tempo.insert(i);
    }
    for (auto i : obj.vec) {
        tempo.insert(i);
    }
    return tempo;
}

set set::operator-(set &obj) {
    set tempo;
    for (auto i : obj.vec) {
        if (!isInSet(i)) {
            tempo.insert(i);
        }
    }
    return tempo;
}

set set::operator*(set &obj) {
    set tempo;
    for (auto i : vec) {
        if (obj.isInSet(i)) {
            tempo.insert(i);
        }
    }
    return tempo;
}

bool set::operator<=(set &object) {
    return (0 < (this->operator*(object)).getSize()) && (getSize() <= object.getSize());
}

bool set::operator==(set &obj) {
    return (getSize() == (this->operator*(obj)).getSize());
}

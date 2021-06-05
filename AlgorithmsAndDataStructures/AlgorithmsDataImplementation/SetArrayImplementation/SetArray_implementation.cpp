//
// Created by Dmytro on 12.03.2021.
//

#include "SetArray_implementation.h"

setArr::setArr() {
    table = new int[universeSize];
    size = 0;
}

bool setArr::checkRangeCorrectness(int x){
    return x < universeSize;
}

void setArr::insert(int x) {
    if (!isInSet(x) && checkRangeCorrectness(x)) {
        for (int i = 0; i < getSize(); i++) {
            if (table[i] > x) {
                int valueToPush = table[i];
                table[i] = x;
                x = valueToPush;
            }
        }
        table[size] = x;
        size++;
    }
}

bool setArr::isInSet(int element) {
    for (int i = 0; i < getSize(); i++) {
        if (table[i] == element)
            return true;
    }
    return false;
}


void setArr::printSet() {
    for (int i = 0; i < getSize(); i++) {
        std::cout << table[i] << " ";
    }
    std::cout << "\n";
}

void setArr::withdraw(int x) {
    if (isInSet(x)) {
        for (int i = 0; i < getSize(); i++) {
            if (table[i] == x) {
                for (int j = i; j < (getSize() - 1); j++) {
                    table[j] = table[j + 1];
                }
                break;
            }
        }
        size--;
    } else {
        std::cout << "Element not found in Set";
    }
}

void setArr::clearSet() {
    for (int i = 0; i < getSize(); ++i) {
        withdraw(table[i]);
    }
}

int setArr::getSize() const {
    return size;
}

setArr setArr::operator+(setArr &s) {
    setArr result;
    for (int i = 0; i < getSize(); i++) {
        result.insert(table[i]);
    }
    for (int i = 0; i < s.getSize(); i++) {
        result.insert(s.table[i]);
    }
    return result;
}

setArr setArr::operator-(setArr &s) {
    setArr result;
    for (int i = 0; i < s.getSize(); i++) {
        int val = s.table[i];
        if (!isInSet(val)) {
            result.insert(val);
        }
    }
    return result;
}

setArr setArr::operator*(setArr &s) {
    setArr result;
    for (int i = 0; i < getSize(); i++) {
        for (int j = 0; j < s.getSize(); j++) {
            if (table[i] == s.table[j]) {
                result.insert(table[i]);
                break;
            }
        }
    }
    return result;
}

bool setArr::operator==(setArr &s) {
    if (getSize() != s.getSize())
        return false;
    else {
        for (int i = 0; i < s.getSize(); i++) {
            int val = s.table[i];
            if (table[i] != val) {
                return false;
            }
        }
        return true;
    }
}

// return (getSize() == (this->operator*(obj)).getSize());

bool setArr::operator<=(setArr &object) {
    return (0 < (this->operator*(object)).getSize()) && (getSize() <= object.getSize());
}

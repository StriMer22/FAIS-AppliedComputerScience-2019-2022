//
// Created by Dmytro Boiko on 14.10.2020.
//

#include <iostream>
#include <vector>
#include <cmath>

int convert(int OctalNumber){
    std::vector<int> numbers;
    int decimalNumber = 0, i = 0;
    while(OctalNumber > 0){
        numbers.push_back(OctalNumber%10);
        OctalNumber /= 10;
        if (numbers[i] >= 8){
            std::cout << "Not an octal number";
            break;
        }
        decimalNumber += numbers[i] * (int) pow(8,i);
        i++;
    }
    return decimalNumber;
}

int main(){
    int number, result;
    std::cout << "Write a number to convert from octal to decimal system:";
    std::cin >> number;
    result = convert(number);
    if (result != 0){
        std::cout << "The result of convert: " << result;
    }
}

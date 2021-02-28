//
// Created by homen on 19.10.2020.
//
#include <iostream>

int recursionFib(int n){
    std::cout << "Recursion: " << n << "\n";
    if (n == 0) return 0;
    if (n == 1) return 1;
    return recursionFib(n-1)+recursionFib(n-2);
}

int iterationFib(int n){
    std::cout << "Iteration: "<< n << "\n";
    int firstNum = 0, secondNum = 1;
    if (n == 0) return 0;
    for (int i = 0; i < n-1; ++i) {
        std::swap(firstNum,secondNum);
        secondNum += firstNum;
    }
    return secondNum;
}

int main(){
    int n = 12;
    std::cout << "Recursion = " << (recursionFib(n)) << "\n";
    std::cout << "Iteration = " << (iterationFib(n));
}
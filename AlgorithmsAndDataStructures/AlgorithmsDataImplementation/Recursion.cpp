//
// Created by Dmytro Boiko on 19.10.2020.
//
#include <iostream>

double power(double x, unsigned int n){
    if(n == 0) return 1.0;
    return x*power(x,n-1);
}

double powerO(double x, unsigned int n, double help = 1.0){
    if(n == 0) return help;
    return powerO(x,n-1,x*help);
}

double iterationPower(double x, unsigned int n){
    if(n == 0) return 1.0;
    double result = 1;
    for (int i = 0; i < n; ++i) {
        result *= x;
    }
    return result;
}

int main(){
    double x;
    unsigned int n;
    std::cout << "Write x and n:" << std::endl;
    std::cin >> x >> n;
    std::cout << "Recursion\n" << power(x,n) << "\n";
    std::cout << "Iteration\n" << iterationPower(x,n) << "\n";
    std::cout << "PowerO\n" << powerO(x,n);
}
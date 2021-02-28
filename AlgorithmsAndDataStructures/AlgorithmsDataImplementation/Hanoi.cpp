//
// Created by Dmytro Boiko on 22.10.2020.
//
#include <iostream>

//amount - ilosc krązków, point1 - stos1, point2 - stos2, temp - pomocniczy stos
void move(int amount, char point1, char point2){
    std::cout <<"Move disk " << amount << " from " << point1 << " to " << point2 << "\n";
}

void moveTower(int amount, char point1, char point2, char temp){
//jeżeli nie ma krążków
    if (amount == 0) return;
// Przesuwamy (n-1) krążków z stosa 1 w pomocniczy stos
    moveTower(amount - 1, point1, temp, point2);
// Przesuwamy n krążek z stosa1 w stos2
    move(amount,point1, point2);
// Przesuwamy (n-1) krążków z pomocniczego stosu w stos2
    moveTower(amount - 1, temp, point2, point1);
}

int main(){
    moveTower(3,'A','C','B');
}
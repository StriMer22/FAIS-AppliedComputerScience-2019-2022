//
// Created by Dmytro Boiko on 26.10.2020.
//
#include <iostream>
#include <string>

using namespace std;

class Zbior{
    string array[9];
    size_t length = sizeof(array) / sizeof(array[0]);
public:
// dodaj element
    void add_elem(const string& element){
        for (auto & i : array) {
            if (i == element){
                break;
            } else if(i.empty()){
                i = element;
                break;
            }
        }
    }
// usuń element
    int remove_element(int delete_element){
        array[delete_element] = "";
        if (delete_element + 1 < length){
            if (!array[delete_element+1].empty()){
                for (int i = delete_element; i < length-1; ++i) {
                    array[i] = array[i+1];
                }
                array[8] = "";
            }
        }
    }
// suma zbiorów
    Zbior summary(const Zbior& zb2){
        Zbior newZbior;
        for (const auto & i : array) {
            newZbior.add_elem(i);
        }
        for (int i = 0; i < length; ++i) {
            string temp = zb2.array[i];
            if (newZbior.array[i] != zb2.array[i]){
                newZbior.add_elem(temp);
            }
        }
        return newZbior;
    }

// Przy jednym argumencie funkcji
//    Zbior intersection(const Zbior& zb2){
//        Zbior newZbior, zbior2;
//        for (const auto & i : array) {
//            newZbior.add_elem(i);
//        }
//        for (int i = 0; i < newZbior.array->length(); ++i) {
//            for (int j = 0; j < zb2.array->length(); ++j) {
//                if (newZbior.array[i] == zb2.array[j]){
//                    zbior2.add_elem(zb2.array[j]);
//                    break;
//                }
//            }
//        }
//        return zbior2;
//    }
// iloczyn zbiorów
    Zbior intersection(const Zbior& zb2, const Zbior zb3) {
        Zbior newZbior;
        for (int i = 0; i < zb2.array->length(); ++i) {
            for (int j = 0; j < zb3.array->length(); ++j) {
                if (zb2.array[i] == zb3.array[j]) {
                    newZbior.add_elem(zb3.array[j]);
                    break;
                }
            }
        }
        return newZbior;
    }
// różnica zbiorów
    Zbior complement(const Zbior& zb){
        Zbior newZbior;
        for (const auto& m : array) {
            for (const auto& n : zb.array) {
                if (m == n){
                    goto cnt;
                }
            }
            newZbior.add_elem(m);
            cnt:;
        }
        return newZbior;
    }
// relacja równości
    void equality(const Zbior& zb){
    Zbior newZbior;
    for (const auto & i : array) {
        newZbior.add_elem(i);
    }
        if (equal(begin(zb.array),end(zb.array),begin(newZbior.array))){
            cout << "\nZbiory są równe";
        } else {
            cout << "\nZbiory nie są równe";
        }
    }
// relacja równoliczności
    void equinumerosity(const Zbior& zb2){
        Zbior newZbior;
        int count1 = 0, count2 = 0;
        for (const auto & i : array) {
            newZbior.add_elem(i);
        }
        for (int i = 0; i < length; ++i) {
            if (newZbior.array[i].empty()){
                count1++;
            }
            if (zb2.array[i].empty()){
                count2++;
            }
        }
        if (count1 != count2){
            cout << "\nZbiory nie są równoliczne";
        } else {
            cout << "\nZbiory są równoliczne";
        }
    }
// relacja zawierania
    bool haveSet(const Zbior& zb2){
        Zbior newZbior;
        for (const auto & i : array) {
            newZbior.add_elem(i);
        }
        int counter = 0, count1 = 0;
        for (int i = 0; i < length; ++i) {
            if (!newZbior.array[i].empty()){
                count1++;
            }
        }
        for (int i = 0; i < length; ++i) {
            for (int j = 0; j < length; ++j) {
                if (newZbior.array[i] == zb2.array[j]){
                    if (!newZbior.array[i].empty() && !zb2.array[i].empty()){
                        counter++;
                    }
                    break;
                }
            }
        }
        return counter == count1;
    }
// wypisz elementy zbioru
    void printArray(){
        for (auto & i : array) {
            cout << i + " ";
        }
    }
// usuń wszystkie elementy ze zbioru
    void deleteAllElements(){
        for (auto & i : array){
            i = "";
        }
        cout << "\nWszystkie elementy usuniete!!";
    }
};

int main(){
    Zbior zb,zb2,zb3;
    zb3.add_elem("111111");
    zb3.add_elem("222222");
    zb.add_elem("111111");
    zb.add_elem("666666");
    zb.add_elem("222222");
    zb2.add_elem("333333");
    zb.add_elem("444444");
    zb.add_elem("555555");
    zb2.add_elem("666666");
    zb.add_elem("777777");
    zb2.add_elem("888888");
    zb.add_elem("999999");
    zb2.add_elem("111111");
    zb2.add_elem("555555");
    zb2.add_elem("222222");
    zb.remove_element(1);
    cout << "Zbiór nr1: " << endl;
    zb.printArray();
    cout << "\nZbiór nr2: " << endl;
    zb2.printArray();
    cout << "\nZbiór nr3: " << endl;
    zb3.printArray();
    if (zb3.haveSet(zb)){cout << "\nZbior3 jest podzbiorem zbioru1";}
    if (zb.haveSet(zb3)){cout << "\nZbior1 jest podzbiorem zbioru3";}
    zb.equinumerosity(zb2);
    zb3.equality(zb);
    cout << "\nSuma zbiorów nr1 i nr2: " << endl;
    zb.summary(zb2).printArray();
    cout << "\nIloczyn zbiorów nr1 i nr2: " << endl;
    zb.intersection(zb,zb2).printArray();
    cout << "\nRóżnica Zbiór1\\Zbiór2: " << endl;
    zb.complement(zb2).printArray();
    cout << "\nRóżnica Zbiór2\\Zbiór1: " << endl;
    zb2.complement(zb).printArray();
    zb.deleteAllElements();
}

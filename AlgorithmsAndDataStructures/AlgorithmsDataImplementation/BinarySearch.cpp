//
// Created by homen on 19.10.2020.
//

#include <iostream>

int binarySearch(int n, int array[], int start, int end){
    if (start > end) return -1;
        int middle = (start+end)/2;
        if (array[middle] == n){
            return middle;
        }else if (n < array[middle])
            binarySearch(n,array,start,middle-1);
        else
            binarySearch(n,array,middle+1,end);
}

int main(){
    int array[] = {2,4,7,6,8,9,10};
    int arrSize = sizeof(array)/sizeof(array[0]);
    int n;
    for(int i = 0; i < arrSize; i++){
        std::cout << array[i] << " ";
    }
    std::cout << "\nWrite a number to find it in array\n";
    std::cin >> n;
    std::cout << "Index of array = " << binarySearch(n,array,0,arrSize-1);
}

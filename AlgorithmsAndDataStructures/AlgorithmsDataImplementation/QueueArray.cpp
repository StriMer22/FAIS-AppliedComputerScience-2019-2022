//
// Created by Dmytro on 12/6/2020.
//
#include <iostream>
#include <cstdlib>
using namespace std;

#define SIZE 10

class queue{
    int *arr;
    int capacity;
    int front;
    int rear;
    int count;

public:
    explicit queue(int size = SIZE);
    ~queue();
    void get();
    void put(int item);
    int elementfront();
    int size();
    bool isEmpty();
    bool isFull();
    void makenull();
    void print();
};
queue::queue(int size){
    arr = new int[size];
    capacity = size;
    front = 0;
    rear = -1;
    count = 0;
}
queue::~queue(){
    delete[] arr;
}
void queue::get(){
    if (isEmpty()){
        cout << "UnderFlow\n";
        exit(EXIT_FAILURE);
    }
    cout << "Removing " << arr[front] << '\n';
    front = (front + 1) % capacity;
    count--;
}
void queue::makenull(){
    int n = size();
    for (int i = 0; i < n; i++){
        get();
    }
}
void queue::put(int item){
    if (isFull()){
        cout << "OverFlow\n";
        exit(EXIT_FAILURE);
    }
    cout << "Added " << item << '\n';
    rear = (rear + 1) % capacity;
    arr[rear] = item;
    count++;
}

int queue::elementfront(){
    if (isEmpty()){
        cout << "UnderFlow\n";
        exit(EXIT_FAILURE);
    }
    return arr[front];
}

int queue::size(){
    return count;
}

bool queue::isEmpty(){
    return (size() == 0);
}

bool queue::isFull(){
    return (size() == capacity);
}

void queue::print() {
    cout << "Queue: \n";
    for (int i = 0; i < size(); ++i) {
        cout << arr[i] << " \n";
    }
}

int main(){
    queue q(5);
    q.put(4);
    q.put(5);
    q.put(3);
    q.print();
    q.put(8);
    cout << "Front element is: " << q.elementfront() << endl;
    q.get();
    cout << "Queue size is " << q.size() << endl;
    if (q.isEmpty())
        cout << "Queue Is Empty\n";
    else
        cout << "Queue Is Not Empty\n";
    q.makenull();
    if (q.isEmpty())
        cout << "Queue Is Empty\n";
    else
        cout << "Queue Is Not Empty\n";
    return 0;
}

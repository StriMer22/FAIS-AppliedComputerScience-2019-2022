//
// Created by Dmytro on 12/6/2020.
//
#include <iostream>
#include <cstdlib>
using namespace std;

#define SIZE 10

class stack{
    int *arr;
    int top;
    int capacity;

public:
    explicit stack(int size = SIZE);
    ~stack();
    void push(int);
    int pop();
    int Top();
    int size();
    bool isEmpty();
    bool isFull();
    void makenull();
};

stack::stack(int size){
    arr = new int[size];
    capacity = size;
    top = -1;
}

stack::~stack(){
    delete[] arr;
}

void stack::push(int x){
    if (isFull()){
        cout << "OverFlow\n";
        exit(EXIT_FAILURE);
    }
    cout << "Inserting " << x << endl;
    arr[++top] = x;
}

int stack::pop(){
    if (isEmpty()){
        cout << "UnderFlow\n";
        exit(EXIT_FAILURE);
    }
    cout << "Removing " << Top() << endl;
    return arr[top--];
}

int stack::Top(){
    if (!isEmpty())
        return arr[top];
    else
        exit(EXIT_FAILURE);
}

void stack::makenull(){
    int n = size();
    for (int i = 0; i < n; ++i) {
        pop();
    }
}

int stack::size(){
    return top + 1;
}

bool stack::isEmpty(){
    return top == -1;
}

bool stack::isFull(){
    return top == capacity - 1;
}

int main(){
    stack pt(5);
    pt.push(1);
    pt.push(2);
    pt.pop();
    pt.push(3);
    pt.push(1);
    pt.push(5);
    cout << "Top element is: " << pt.Top() << endl;
    cout << "Stack size is " << pt.size() << endl;
    pt.pop();
    if (pt.isEmpty())
        cout << "Stack Is Empty\n";
    else
        cout << "Stack Is Not Empty\n";
    pt.makenull();
    if (pt.isEmpty())
        cout << "Stack Is Empty\n";
    else
        cout << "Stack Is Not Empty\n";
    return 0;
}

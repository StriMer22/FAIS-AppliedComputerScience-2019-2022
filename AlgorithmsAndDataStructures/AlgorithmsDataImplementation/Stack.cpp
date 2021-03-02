//
// Created by Dmytro Boiko on 16.11.2020.
//
#include <iostream>

using namespace std;

class Stack {
private:
    struct Node{
        int d;
        Node *p;
    };
    Node* head;
public:
    Stack();
    ~Stack();
    void Push(int d);
    int Pop();
    int Top();
    bool empty();
    void makenull();
    void Print();
};

Stack::Stack() {
    head = nullptr;
}

Stack::~Stack() {
    while (head){
        Node* pv = head;
        head = head->p;
        delete pv;
    }
}

void Stack::Push(int d) {
    Node *pv = new Node;
    pv->d = d;
    pv->p = head;
    head = pv;
}

int Stack::Pop(){
    Node* temp = head;
    head = head->p;
    temp->p = nullptr;
    free(temp);
    return 0;
}

bool Stack::empty() {
    return head == nullptr;
}

void Stack::makenull() {
    while (!empty()){
        delete head;
        head = head->p;
    }
}

int Stack::Top() {
    return head->d;
}

void Stack::Print() {
    cout << "Stack: " << endl;
    Node * node = head;
    if (empty()){
        cout << "Stack is empty" << endl;
    }
    while (node != nullptr) {
        cout << "|" << node->d << "|\n";
        node = node->p;
    }
}

int main(){
    Stack stack;
    stack.Print();
    cout << "Enter the list: " << endl;
    for (int i = 0; i < 5; ++i) {
        int z;
        cout << ">>";
        cin >> z;
        stack.Push(z);
    }
    stack.Print();
    cout << "Element na szczycie stosu: " << stack.Top() << endl;
    stack.Pop(); // Usuwamy element na szczycie stosu
    stack.Print();
    stack.makenull(); // usuwamy wszystkie elementy
    stack.Print();
}



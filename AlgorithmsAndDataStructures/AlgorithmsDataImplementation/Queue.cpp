//
// Created by Dmytro on 11.16.2020.
//
#include <iostream>

using namespace std;

class Queue{
private:
    struct Node{
        int d;
        Node *p;
    };
    Node *head, *tail;
public:
    Queue();
    ~Queue();
    void put(int d);
    int get();
    int elementfront();
    bool empty();
    void makenull();
    void Print();
};

Queue::Queue() {
    head = nullptr;
    tail = nullptr;
}

Queue::~Queue() {
    while (head){
        Node* pv = head;
        head = head->p;
        delete pv;
    }
}

void Queue::put(int d) {
    Node *curr = new Node;
    curr->d = d;
    curr->p = nullptr;
    if (empty()){
        head = tail = curr;
    } else {
        tail->p = curr;
        tail = curr;
    }
}

int Queue::get(){
    Node* temp = head;
    head = head->p;
    free(temp);
    return 0;
}

bool Queue::empty() {
    return head == nullptr;
}

void Queue::makenull() {
    while (!empty()){
        delete head;
        head = tail->p;
    }
}

int Queue::elementfront() {
    return head->d;
}

void Queue::Print() {
    cout << "\nQueue: " << endl;
    Node * node = head;
    if (empty()){
        cout << "Queue is empty" << endl;
    }
    while (node != nullptr) {
        cout << "|" << node->d << "|\t";
        node = node->p;
    }
    cout << "\n";
}

int main(){
    Queue queue;
    queue.Print();
    cout << "Enter the queue: " << endl;
    for (int i = 0; i < 5; ++i) {
        int z;
        cout << ">>";
        cin >> z;
        queue.put(z);
    }
    queue.Print();
    queue.get(); // Usuwamy pierwszy element kolejki
    queue.Print();
    cout << "Pierwszy element kolejki: " << queue.elementfront() << endl;
    queue.Print();
    queue.makenull(); // usuwamy wszystkie elementy
    queue.Print();
}



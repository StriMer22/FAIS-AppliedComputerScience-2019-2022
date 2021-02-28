//
// Created by Dmytro Boiko on 02.11.2020.
//
#include <iostream>

using namespace std;

class Node{
    int field;
    Node *ptr;
    friend class List;
    Node(){}
    explicit Node(int data){
        field = data;
        ptr = nullptr;
    }
};

class List{
    Node *head;
    int count = 0;
    Node* Prev(Node *);
public:
    List(){
        head = nullptr;
    }
    ~List(){
        delete head;
    }
    static int Retrieve(Node* p){
        return p->field;
    }
    void Print();
    Node* Insert(int value, Node *p);
    Node* Delete(Node*);
    Node* Locate(int value);
    void reverse();
    Node* getLast();
    Node* getFirst(){
        return head;
    }
    Node* swapPairs(Node* pNode);
    static Node* swap(Node* node);
    static Node* next(Node *);

};
// wstawia komórkę z elementem x na pozycję next komórki o wskaźniku p
Node* List::Insert(int val, Node* p = nullptr) {
    Node *elem = new Node();
    elem->field = val;
    count++;
    if (p == nullptr) {
        if (head == nullptr) {
            elem->ptr = nullptr;
            head = elem;
        } else {
            elem->ptr = head;
            head = elem;
        }
        return elem;
    }
    elem->ptr = p->ptr;
    p->ptr = elem;
    return elem;
}
// usuwa komórkę o wskaźniku p
Node* List::Delete(Node* node) {
    if (node == nullptr){
        return nullptr;
    }
    count--;
    if(node == head){
        head = node->ptr;
        delete node;
        return head;
    }
    Node* prev = Prev(node);
    prev->ptr = node->ptr;
    delete node;
    return prev;
}


// zwraca wskaźnik do kolejnej komórki po komórce o wskaźniku p
Node* List::next(Node * node) {
    return node->ptr;
}
// zwraca wskaźnik do komórki poprzedzającej komórkę o wskaźniku p
Node* List::Prev(Node * node) {
    if (node == head) return nullptr;
    Node* p = head;
    while (p->ptr != node)
        p = p->ptr;
    return p;
}
// zwraca wskaźnik do ostatniej komórki na liście
Node* List::getLast() {
    Node* p = head;
    while (next(p) != nullptr)
        p = next(p);
    return p;
}
// zwraca wskaźnik do pierwszej komórki z elementem x
Node* List::Locate(int value) {
    int i = 0;
    for(Node* p = getFirst(); p != nullptr; p = next(p)){
        if(p->field == value)
            return p;
        i++;
    }
    return nullptr;
}
//*********************************************Kolokwium****************************************//
 void List::reverse(){
    Node* current = head;
    Node *prev = nullptr, *ptr = nullptr;
    while (current != nullptr) {
        ptr = next(current);
        current->ptr = prev;
        prev = current;
        current = ptr;
    }
    head = prev;
}
//** Kolokwium wersja **//
Node* List::swap(Node* pNode) {
    if(!pNode)return pNode;
    Node* first = pNode;
    Node* second = pNode->ptr;
    Node* dummy = new Node(0);
    dummy->ptr = first;
    Node* prev = pNode;
    while(second){
        Node* temp = second->ptr;
        first->ptr = second->ptr;
        second->ptr = first;
        prev->ptr = second;
        prev = first;
        if(temp){
            first = temp;
            second = temp ->ptr;
        }
        else break;
    }
    return dummy->ptr;
}

//** Poprawiona wersja **//
Node* List::swapPairs(Node*) {
    if(!head)return head;
    Node* first = head;
    Node* second = head->ptr;
    head = second;
    while(second){
        Node* temp = second->ptr;
        second->ptr = first;
        if(temp == nullptr || temp->ptr == nullptr){
            first->ptr = temp;
            break;
        }
        first->ptr = temp->ptr;
        first = temp;
        second = first->ptr;
    }
    return head;
}
//*********************************************Kolokwium****************************************//

// wyświetla wszystkie elementy listy
void List::Print(){
    Node* point = head;
    cout << "List: " << endl;
    while (point != nullptr){
        cout << Retrieve(point) << " ";
        point = next(point);
    }
}

int main(){
    int read;
    List list;
    list.Print();
    cout << "Enter the list: " << endl;
    for (int i = 0; i <9; ++i) {
        int z;
        cout << ">>";
        cin >> z;
        list.Insert(z);
    }
    list.Print();
    cout << "\nFirst element: " << List::Retrieve(list.getFirst());
    cout << "\nLast element: " << List::Retrieve(list.getLast());
    Node *p = list.getFirst();
    cout << "\nEnter the elements you want to delete: " << endl;
    cin >> read;
    do {
        if (List::Retrieve(p) == read)
            p = list.Delete(p);
        else
            p = list.next(p);
    }while (p != nullptr);
    list.Print();
    list.reverse();
    list.Print();
    //Dodawanie elementu na koniec listy
//    cout << "\nEnter the list: " << endl;
//    Node *s = list.getLast();
//    for (int i = 0; i < 5; ++i) {
//        int z;
//        cout << ">> ";
//        cin >> z;
//        s = list.Insert(z,s);
//    }
//    list.Print();
    //zwraca wskaźnik do pierwszej komórki z elementem x
//    list.Locate(7);
    list.swapPairs(list.getFirst());
    list.Print();
    list.swap(list.Locate(6));
    list.Print();
}

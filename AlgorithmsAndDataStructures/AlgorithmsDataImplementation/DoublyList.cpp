#include <iostream>

using namespace std;

template<class T>
class DoublyLinkedList{
    struct Node{
        T data;
        Node* next;
        Node* prev;
        explicit Node(T val): data(val), next(nullptr), prev(nullptr) {}
    };
    Node *head, *tail;

public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }
    ~DoublyLinkedList(){
        Node *tmp;
        while (head){
            tmp = head;
            head = head->next;
            delete tmp;
        }
        head = nullptr;
    }

    DoublyLinkedList(const DoublyLinkedList<T> & dll) = delete;
    DoublyLinkedList& operator=(DoublyLinkedList const&) = delete;

    void insertFront(T val){
        Node *node = new Node(val);
        if (head == nullptr){
            head = node;
            tail = node;
        }else{
            node->next = head;
            head = node;
            node->next->prev = node;
        }
    }
    void insertBack(T val){
        Node *node = new Node(val);
        if(tail->next == nullptr){
            tail->next = node;
            tail = node;
        }
    }
    void Delete(T val){
        Node* find = findVal(val);
        Node *tmp = head;
        if(tmp == find){
            head = Next(tmp);
        }else{
            while(find != nullptr){
                if(Next(tmp) == find){
                    tmp->next = Next(find);
                    find->next->prev = tmp;
                    delete find;
                    return;
                }
                tmp = Next(tmp);
            }
        }
    }

    Node* successor = nullptr;
    Node* reverseN(Node* node, int n ){
        if(n == 1){
            successor = node->next;
            return node;
        }
        Node* last = reverseN(node->next, n - 1);
        node->next->next = node;
        node->next = successor;
        return last;
    }
    Node* reverseBetween(Node* pNode, int m, int n) {
        if(m == 1){
            return reverseN(pNode, n);
        }
        pNode->next = reverseBetween(pNode->next, m - 1, n - 1);
        return pNode;
    }

    Node *Next(Node* p) {
        return p->next;
    }
    Node *Prev(Node* p) {
        return p->prev;
    }
    Node* getLast() {
        return tail;
    }
    Node* getFirst(){
        return head;
    }
    Node* locate(T val){
        Node* find = findVal(val);
        if(find->data == val)
            return find;
        return nullptr;
    }
    T Retrieve(Node* p){
        return p->data;
    }
    template <class U>
    friend std::ostream & operator<<(std::ostream & os, const DoublyLinkedList<U> & dll){
        dll.display(os);
        return os;
    }
private:
    Node *findVal(T n){
        Node *node = head;
        while(node != nullptr){
            if(node->data == n)
                return node;
            node = node->next;
        }
        std::cerr << "No such element in the list \n";
        return nullptr;
    }
    void display(std::ostream& out = std::cout) const{
        Node *node = head;
        while(node != nullptr){
            out << node->data << " ";
            node = node->next;
        }
    }
};

int main(){
    DoublyLinkedList<int> l1;
    l1.insertFront(3);
    l1.insertBack(5);
    l1.insertBack(12);
    l1.insertFront(6);
    l1.insertBack(88);
    std::cout<<l1<<"\n";
    l1.reverseN(l1.getFirst(),1);
    std::cout<<l1<<"\n";
//    l1.Delete(12);

//    cout << "First " << l1.Retrieve(l1.getFirst()) << endl;
//    cout << "Last " << l1.Retrieve(l1.getLast()) << endl;
//    cout << "Second element " <<  l1.Retrieve(l1.Next(l1.getFirst())) << endl;
//    cout << "The one before last " <<  l1.Retrieve(l1.Prev(l1.getLast())) << endl;
//    cout << l1.locate(88) << endl;
    return 0;
}
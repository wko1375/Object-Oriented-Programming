// Doubly linked list
//  Test code

#include <cstdlib>
#include <iostream>
using namespace std;

class List {
    friend ostream& operator<<(ostream& os, const List& DLL){
        if(DLL.size() == 0){
            return os;
        }
        List::Node* ptr = DLL.head -> next;
        while(ptr != DLL.tail){
            os << ptr -> data << " ";
            ptr = ptr -> next;
        }
        os << endl;
        return os;
    }
    struct Node{
        Node(int data = 0, Node* next = nullptr, Node* prev = nullptr) : data(data), next(next), prev(prev) {}
        int data;
        Node* next;
        Node* prev;
    };
public:
    class ListIterator {
        friend class List;
        friend ostream& operator<<(ostream& os, const ListIterator& L){
            os << L.ptr -> data << " ";
            return os;
        }
        friend bool operator==(const ListIterator& L1, const ListIterator& L2){
            if(L1.ptr == L2.ptr){
                return true;
            }
            else{
                return false;
            }
        }
        friend bool operator!=(const ListIterator& L1, const ListIterator& L2){
            if(L1.ptr == L2.ptr){
                return false;
            }
            else{
                return true;
            }
        }
    public:
        ListIterator(Node* nptr) : ptr(nptr){}
        ListIterator(const ListIterator& L){
            ptr = L.ptr;
        }
        ListIterator operator++(){
            ptr = ptr -> next;
            return *this;
        }
        ListIterator operator--(){
            ptr = ptr -> prev;
            return *this;
        }
        int& operator*(){
            return ptr -> data;
        }
        Node* ptr = nullptr;
    };
    List(){}
    ~List(){
        Node* ptr = head;
        Node* ptr2 = head -> next;
        while(ptr != tail){
            delete ptr;
            ptr = ptr2;
            ptr2 = ptr2 -> next;
        }
        delete tail;
    }
    List(const List& L){
        Node* ptr = L.head -> next;
        while(ptr != L.tail){
            push_back(ptr -> data);
            ptr = ptr -> next;
        }
        return;
    }
    List& operator =(const List& L){
        if(&L == this){
            return *this;
        }
        length = 0;
        Node* ptr1 = head -> next;
        Node* ptr2 = ptr1 -> next;
        while(ptr2 != tail){
            delete ptr1;
            ptr1 = ptr2;
            ptr2 = ptr2 -> next;
        }
        delete ptr1;
        tail -> prev = head;
        head -> next = tail;
        Node* optr = L.head -> next;
        while(optr != L.tail){
            push_back(optr -> data);
            optr = optr -> next;
        }
        return *this;
    }
    void push_back(int data){
        Node* n = new Node(data);
        n -> next = tail;
        n -> prev = tail -> prev;
        tail -> prev -> next = n;
        tail -> prev = n;
        length ++;
        return;
    }
    void pop_back(){
        if(size() == 0){
            return;
        }
        Node* p = tail -> prev;
        Node* ptr = tail -> prev -> prev;
        tail -> prev = ptr;
        ptr -> next = tail;
        delete p;
        length --;
        return;
    }
    void push_front(int data){
        Node* n = new Node(data);
        n -> prev = head;
        n -> next = head -> next;
        head -> next -> prev = n;
        head -> next = n;
        length ++;
        return;
    }
    void pop_front(){
        if(size() == 0){
            return;
        }
        Node* p = head -> next;
        Node* ptr = head -> next -> next;
        head -> next = ptr;
        ptr -> prev = head;
        delete p;
        length --;
        return;
    }
    List::Node* front(){
        if(tail -> prev == head){
            return nullptr;
        }
        else{
            return tail -> prev;
        }
    }
    List::Node* back();
    int& operator [](int index)const{
        int i = 0;
        Node* ptr = head -> next;
        while(i < index){
            ptr = ptr -> next;
            i++;
        }
        return ptr -> data;
    }
    int size()const{
        return length;
    }
    void clear(){
        if(size() == 0){
            return;
        }
        if(size() == 1){
            delete head -> next;
            head -> next = tail;
            tail -> prev = head;
            length = 0;
            return;
        }
        else{
            List::Node* ptr = head -> next;
            while(ptr != tail){
                head -> next = ptr -> next;
                ptr -> next -> prev = head;
                delete ptr;
                ptr = head -> next;
            }
            length = 0;
            cout << *this;
            return;
        }
    }
    ListIterator begin(){
        if(size() == 0){
            return ListIterator(tail);
        }
        return ListIterator(head->next);
    }
    ListIterator end(){
        return ListIterator(tail);
    }
    ListIterator& insert(ListIterator L, int data){
        Node* newNode = new Node(data, L.ptr, L.ptr -> prev);
        L.ptr -> prev -> next = newNode;
        L.ptr -> prev = newNode;
        L.ptr = newNode;
        length++;
        return L;
    }
    ListIterator& erase(ListIterator L){
        Node* p = L.ptr -> prev;
        L.ptr -> next -> prev = p;
        p -> next = L.ptr -> next;
        delete L.ptr;
        ListIterator* L1 = new ListIterator(p -> next);
        length --;
        return *L1;
    }
private:
    int length = 0;
    Node* head = new Node(0, tail, nullptr);
    Node* tail = new Node(0, nullptr, head);
};

void printListInfo(List& myList) {
    cout << "size: " << myList.size()
         << ", front: " << myList.begin()
         << ", back(): " << myList.end()
         << ", list: " << myList << endl;
}

// Task 8
void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << endl;
    cout << "Leaving doNothing\n";
}

int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    cout << "===================\n";

    // Task3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i){
        myList.push_back(i*i);
    };
    printListInfo(myList);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;

    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    for (List::ListIterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";

    // Task 6jj
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***

    cout << "===================\n";

    // Task 8
    cout << "\n------Task Eight------\n";
    cout << "Copy control\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Calling doNothing(myList)\n";
    doNothing(myList);
    cout << "Back from doNothing(myList)\n";
    printListInfo(myList);

    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    List listTwo;
    for (int i = 0; i < 10; ++i) {
        listTwo.insert(listTwo.begin(), i*i);
    }
    printListInfo(listTwo);
    cout << "listTwo = myList\n";
    listTwo = myList;
    cout << "myList: ";
    printListInfo(myList);
    cout << "listTwo: ";
    printListInfo(listTwo);
    cout << "===================\n";
}

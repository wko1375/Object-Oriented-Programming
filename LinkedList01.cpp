#include <iostream>
#include <vector>
#include <cstdlib> // To allow NULL if no other includes
#include <unordered_set>
using namespace std;

struct Node {
    Node(int data = 0, Node* next = NULL) : data(data), next(next) {}
    int data;
    Node* next;
};

void listInsertHead(Node*& headPtr, int entry) {
    headPtr = new Node(entry, headPtr);
}

// Should free up your nodes, of course...
void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
}

// This might be useful for setting up test cases. Feel free to use it
// or not as you like. Example of using would be:
// Node* myList = listBuild({1, 4, 9, 16}); // builds a list of: 1 4 9 16
Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
        listInsertHead(result, vals[index-1]);
    }
    return result;
}

void display(Node* node){
    while(node != nullptr){
        cout << node -> data << " ";
        node = node -> next;
    }
    cout << endl;

}

void spliceInto(Node* firstNode, Node* insertedNode){
    Node* nextNodeOriginalList = firstNode -> next;
    Node* lastNodeInsertedList = nullptr;
    Node* firstNodePtr = firstNode;
    Node* insertedNodePtr = insertedNode;
    while(firstNode != nullptr){
        cout << firstNode -> data << " ";
        firstNode = firstNode -> next;
    }
    cout << endl;
    while(insertedNode != nullptr){
        cout << insertedNode -> data << " ";
        if(insertedNode -> next == nullptr){
            lastNodeInsertedList = insertedNode;
        }
        insertedNode = insertedNode -> next;
    }
    cout << endl;
    firstNode = firstNodePtr;
    insertedNode = insertedNodePtr;
    lastNodeInsertedList -> next = nextNodeOriginalList;
    firstNode -> next = insertedNode;
    while(firstNode != nullptr){
        cout << firstNode -> data << " ";
        firstNode = firstNode -> next;
    }
}

Node* sublist(Node* original, Node* sublist){
    display(original);
    display(sublist);
    Node* originalptr = original;
    Node* sublistptr = sublist;
    while(original != nullptr){
        if(original -> data == sublist -> data){
            while(original -> data == sublist -> data){
                if(sublist -> next == nullptr){
                    return originalptr;
                }
                original = original -> next;
                sublist = sublist -> next;
            }
            original = originalptr -> next;
            originalptr = original;
            sublist = sublistptr;
        }
        else{
            original = original -> next;
            originalptr = original;
        }
    }
    cout << "Match not found" << endl;
    return nullptr;
}


Node* sharedNode(Node* list1, Node* list2){
    unordered_set<Node*> unsharedNodes;
    while(list1 != nullptr){
        unsharedNodes.insert(list1);
        list1 = list1 -> next;
    }
    cout << unsharedNodes.size();
    while(list2 != nullptr){
        display(list2);
        if(unsharedNodes.find(list2) != unsharedNodes.end()){
            display(list2);
            return list2;
        }
        list2 = list2 -> next;
    }
    return nullptr;
}


int main() {
    cout << "Part Two: " << endl;
    Node* first = new Node (1);
    Node* second = new Node(2);
    Node* third = new Node(3);
    Node* fourth = new Node(2);
    Node* fifth = new Node(3);
    Node* sixth = new Node(2);
    Node* seventh = new Node(4);
    Node* eighth = new Node(5);
    Node* ninth = new Node(6);
    first -> next = second;
    second -> next = third;
    third -> next = fourth;
    fourth -> next = fifth;
    fifth -> next = sixth;
    sixth -> next = seventh;
    seventh -> next = eighth;
    eighth -> next = ninth;


    Node* test1 = new Node(1);

    Node* test2 = new Node(9);
    Node* test3 = new Node(3, test2);

    Node* test4 = new Node(3);
    Node* test5 = new Node(2, test4);

    Node* test6 = new Node(4);
    Node* test7 = new Node(2, test6);
    Node* test8 = new Node(3, test7);
    Node* test9 = new Node(2, test8);

    display(sublist(first, test9));

    cout << "Part Three: " << endl;
    sharedNode(first, fifth);



}

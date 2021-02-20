#include <iostream>
#include <vector>
#include <string>
#include "DLL.h"
#include <algorithm>
#include <array>
using namespace std;

//Task 1 Function
void printDigitsR(int n) {
    if (n < 10) {
        cout << n << ' ';
    } else {
        cout << n % 10 << ' ';
        printDigitsR(n / 10);
    }
}

int printBits(int n) {
    if (n < 2) {
        cout << n << ' ';
    }
    else {
        printBits(n/2);
        cout << n % 2 << ' ';
    }
}
bool evenOnes(int num){
    if(num < 2){
        return(num == 0);
    }
    else{
        int newnum = num / 2;
        int rest = num % 2;
        bool recursionResult = evenOnes(newnum);
        if(rest == 1){
            return !recursionResult;
        }
        return recursionResult;
    }
}

//Task 2 Function
Node* newAddList(const Node* n1, const Node* n2){
    if(n1  == nullptr && n2 == nullptr){
        return nullptr;
    }
    if(n2 == nullptr){
        Node* newNode = new Node(n1 -> data , newAddList(n1 -> next, n2));
        return newNode;
    }
    if(n1 == nullptr){
        Node* newNode = new Node(n2 -> data, newAddList(n1, n2 -> next));
        return newNode;
    }
    else{
        Node* newNode = new Node(n1 -> data + n2 -> data, newAddList(n1 -> next, n2 -> next));
        return newNode;
    }
}

//Task 3 Function

struct TNode {
    TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr)
            : data(data), left(left), right(right) {}
    int data;
    TNode *left, *right;
};

int maxVal(TNode* root) {
    if(root == nullptr){
        throw invalid_argument("Tree is nullptr");
    }
    if(root -> left == nullptr && root -> right == nullptr){
        return root -> data;
    }
    if(root -> left == nullptr){
        return max(root -> data, maxVal(root -> right));
    }
    if(root -> right == nullptr){
        return max(root -> data, maxVal(root -> left));
    }
    else{
        return max(root -> data, max(maxVal(root -> left), maxVal(root -> right)));
    }
}

//Task 4 function


bool palindrome(char* arr, int arraySize){
    if(arraySize == 1){
        return true;
    }
    if(arraySize == 2){
        if(arr[0] == arr[arraySize - 1]){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        if(arr[0] == arr[arraySize - 1]){
            return palindrome(arr + 1, arraySize - 2);
        }
    }
}

//Task 5 function
int tower(int disks, char origin, char spare, char target){
    if(disks == 1){
        return 1;
    }
    else{
        int result = tower(disks - 1, origin, target, spare) + 1;
        int result2 = tower(disks - 1, spare, origin, target);
        return result + result2;
    }
}


void mystery(int n) {
    if (n > 1) {
        cout << 'a';
        mystery(n/2);
        cout << 'b';
        mystery(n/2);
    }
    cout << 'c';
}
int main() {
    cout << "Task 1" << endl;
    int number = 11;
    cout << boolalpha << evenOnes(number) << endl << endl;

    cout << "Task 2" << endl << endl;
    Node* node1 = new Node(1);
    Node* node2 = new Node(2, node1);
    Node* node3 = new Node(3, node2);
    Node* node4 = new Node(4, node3);
    Node* node5 = new Node(5, node4);

    Node* node = new Node(100);
    Node* nodeA = new Node(-1, node);
    Node* nodeB = new Node(-2, nodeA);
    Node* nodeC = new Node(-3, nodeB);
    Node* nodeD = new Node(-4, nodeC);
    Node* nodeE = new Node(-5, nodeD);

    Node* newNode = newAddList(node5, nodeE);
    while(newNode != nullptr){
        cout << newNode -> data << " ";
        newNode = newNode -> next;
    }
    cout << endl;



    cout << "Task 3" << endl;
    TNode a(1), b(2), c(4), d(32, &a, &b), e(16, &c), f(8, &d, &e);
    try {
        maxVal(&f);
    }
    catch (invalid_argument& IA){
        cout << "Invalid Argument" << IA.what() << endl;
    }
    cout << endl << endl;

    cout << "Task 4" << endl;
    char s[] = "racecar";
    cout << boolalpha << palindrome(s, 7) << endl;
    cout << endl;

    cout << "Task 5" << endl;
    cout << tower(10, 'a', 'b', 'c');
    mystery(4);
}

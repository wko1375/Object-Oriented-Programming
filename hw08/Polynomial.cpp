//
// Created by William on 4/18/2018.
//

#include "Polynomial.h"
#include <string>
#include <vector>
#include <tgmath.h>
#include <algorithm>
using namespace std;

Node::Node(int data, Node *next) :
        data(data), next(next){}

Node::Node(const Node& node) {
    data = node.data;
    next = node.next;
}

ostream& operator<<(ostream& os, const DLL& list){
    os << "Head -> ";
    if(list.length() == 0){
        os << 0 << " -> ";
        os << "Tail";
        return os;
    }
    Node* curr = list.head -> next;
    while(curr != list.tail){
        os << curr -> data << " -> ";
        curr = curr -> next;
    }
    os << "Tail" << endl;
    return os;
}

DLL::DLL(){}

DLL::~DLL() {
    clear();
}

DLL::DLL(const DLL& list){
    if(list.size == 0){
        return;
    }
    Node* curr = list.head -> next;
    while(curr != list.tail){
        push_back(curr -> data);
        curr = curr -> next;
    }
}

DLL& DLL::operator=(const DLL &list) {
    if(&list == this){ return *this; }
    if(list.size == 0){
        clear();
        return *this;
    }
    else{
        clear();
        Node* curr = list.head -> next;
        while(curr != list.tail){
            push_back(curr -> data);
            curr = curr -> next;
        }
        return *this;
    }
}

void DLL::push_back(double data){
    if(length() == 0){
        Node* newNode = new Node(data, tail);
        head -> next = newNode;
        size += 1;
        return;
    }
    Node* curr = head;
    while(curr -> next != tail){
        curr = curr -> next;
    }
    Node* newNode = new Node(data, tail);
    curr -> next = newNode;
    size += 1;
}

void DLL::push_front(double data){
    if(size == 0){
        Node* newNode = new Node(data, tail);
        head -> next = newNode;
        size += 1;
        return;
    }
    Node* curr = head;
    Node* next = head -> next;
    Node* newNode = new Node(data, next);
    curr -> next = newNode;
    size += 1;
}

void DLL::pop_front(){
    if(size == 0){
        return;
    }
    Node* curr = head;
    Node* deleted = head -> next;
    Node* next = head -> next -> next;
    delete deleted;
    curr -> next = next;
    size -= 1;
}

void DLL::pop_back(){
    if(size == 0){
        return;
    }
    Node* prev = head;
    while(prev -> next -> next != tail){
        prev = prev -> next;
    }
    Node* curr = prev -> next;
    delete curr;
    prev -> next = tail;
    size -= 1;
}

void DLL::remove(int degree){
    if(size == 0){return;}
    int count = 0;
    Node* curr = head;
    while(count < degree - 1){
        curr = curr -> next;
        count += 1;
    }
    Node* deleted = curr -> next;
    Node* next = deleted -> next;
    delete deleted;
    curr -> next = next;
    size -= 1;

}

void DLL::clear(){
    if(size == 0){
        return;
    }
    Node* curr = head -> next;
    Node* prev = head;
    while(curr != tail){
        prev = curr;
        curr = curr -> next;
        delete prev;
    }
    head -> next = tail;
    size = 0;
}

int DLL::length() const {
    return size;
}

//Polynomial Class

//Friend Functions

ostream& operator<<(ostream& os, const Polynomial& p){
    if(p.nums.size == 0){
        os << 0 << endl;
        return os;
    }
    Node* curr = p.nums.head -> next;
    string op = "";
    int exp = 0;
    while(curr != p.nums.tail){
        if(curr -> data == 0){
            if(op.length() > 2 && op[1] == '+'){
                op = op.substr(2, op.length());
            }
            exp += 1;
            curr = curr -> next;
            continue;
        }
        if(exp == 0){
            op = to_string(curr -> data) + op;
            if(curr -> next != p.nums.tail){
                op = " + " + op;
            }
            exp += 1;
            curr = curr -> next;
            continue;
        }
        if(curr -> data == 1){
            if(exp == 1){
                op = "x" + op;
                if(curr -> next != p.nums.tail){
                    op = " + " + op;
                }
                exp += 1;
                curr = curr -> next;
                continue;
            }
            if(exp != 1){
                op = "x^" + to_string(exp) + op;
                if(curr -> next != p.nums.tail){
                    op = " + " + op;
                }
                exp += 1;
                curr = curr -> next;
                continue;
            }
        }
        if(curr -> data != 1){
            if(exp == 1){
                op = to_string(curr -> data) + "x" + op;
                if(curr -> next != p.nums.tail){
                    op = " + " + op;
                }
                exp += 1;
                curr = curr -> next;
                continue;
            }
            if(exp != 1){
                op = to_string(curr -> data) + "x^" + to_string(exp) + op;
                if(curr -> next != p.nums.tail){
                    op = " + " + op;
                }
                exp += 1;
                curr = curr -> next;
                continue;
            }
        }
    }
    if(op.length() > 2 && op[1] == '+'){
        op = op.substr(2, op.length());
    }
    os << op;
    os << endl;
    return os;
}

bool operator!=(const Polynomial& p, const Polynomial& p2){
    return !(p.operator==(p2));
}

Polynomial& operator+(const Polynomial& p, const Polynomial& p2){
    vector<double> newPoly;
    if(p.degree <= p2.degree){
        Node* shorter = p.nums.head -> next;
        Node* longer = p2.nums.head -> next;
        while(shorter != p.nums.tail){
            newPoly.insert(newPoly.begin(), shorter -> data + longer -> data);
            shorter = shorter -> next;
            longer = longer -> next;
        }
        while(longer != p2.nums.tail){
            newPoly.insert(newPoly.begin(), longer -> data);
            longer = longer -> next;
        }
    }
    else{
        Node* shorter = p2.nums.head -> next;
        Node* longer = p.nums.head -> next;
        while(shorter != p2.nums.tail){
            newPoly.insert(newPoly.begin(), shorter -> data + longer -> data);
            shorter = shorter -> next;
            longer = longer -> next;
        }
        while(longer != p.nums.tail){
            newPoly.insert(newPoly.begin(), longer -> data);
            longer = longer -> next;
        }
    }
    Polynomial* np = new Polynomial(newPoly);
    return *np;
}

//Member Functions

Polynomial::Polynomial(std::vector<double> num) {
    int d = 0;
    for(size_t i = 0; i < num.size(); i++){
        nums.push_front(num[i]);
        d += 1;
    }
    degree = d;
}

Polynomial::Polynomial() {
    degree = 0;
}

Polynomial::~Polynomial(){
    nums.clear();
}

Polynomial::Polynomial(const Polynomial &p) {
    nums = p.nums;
    degree = p.degree;
}

Polynomial& Polynomial::operator=(const Polynomial& p) {
    if(&p == this){
        return *this;
    }
    else{
        nums.clear();
        nums = p.nums;
        degree = p.degree;
        return *this;
    }
}

Polynomial& Polynomial::operator+=(const Polynomial& p){
    Node* curr = nums.head -> next;
    Node* oCurr = p.nums.head -> next;
    while(curr != nums.tail && oCurr != p.nums.tail){
        curr -> data += oCurr -> data;
        curr = curr -> next;
        oCurr = oCurr -> next;
    }
    return *this;
}

bool Polynomial::operator ==(const Polynomial& p)const{
    if(degree != p.degree){
        return false;
    }
    Node* curr = nums.head;
    Node* oCurr = p.nums.head;
    while(curr != nums.tail){
        if(curr -> data != oCurr -> data){
            return false;
        }
        curr = curr -> next;
        oCurr = oCurr -> next;
    }
    return true;
}

double Polynomial::evaluate(double arg) const {
    Node* curr = nums.head -> next;
    double ans = 0;
    int degree = 0;
    while(curr != nums.tail){
        if(degree > 0){
            ans += (curr -> data * pow(arg, degree));
        }
        else{
            ans += curr -> data;
        }
        curr = curr -> next;
        degree += 1;
    }
    return ans;
}







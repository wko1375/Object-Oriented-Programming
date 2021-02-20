//
// Created by William on 4/18/2018.
//


#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>
#include <vector>

class Polynomial;

class Node {
public:
    Node(int data = 0, Node* next = nullptr);
    Node(const Node& node);
    int data;
    Node* next;
};

class DLL{
    friend class Node;
    friend class Polynomial;
    friend std::ostream& operator<<(std::ostream& os, const DLL& list);
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);
    friend Polynomial& operator+(const Polynomial& p, const Polynomial& p2);
public:
    DLL();
    DLL(const DLL& list);
    ~DLL();
    DLL& operator=(const DLL& list);
    void push_back(double data);
    void push_front(double data);
    void pop_front();
    void pop_back();
    void remove(int degree);
    void clear();
    int length()const;
private:
    Node* head = new Node(0, tail);
    Node* tail = new Node(0, nullptr);
    int size = 0;
};

class Polynomial {
    friend class DLL;
    friend bool operator!=(const Polynomial& p, const Polynomial& p2);
    friend std::ostream& operator <<(std::ostream& os, const Polynomial& p);
    friend Polynomial& operator+(const Polynomial& p, const Polynomial& p2);
public:
    Polynomial(std::vector<double> num);
    Polynomial();
    ~Polynomial();
    Polynomial(const Polynomial& p);
    Polynomial& operator=(const Polynomial& p);
    Polynomial& operator +=(const Polynomial& p);
    bool operator ==(const Polynomial& p)const;
    double evaluate(double arg)const;
private:
    int degree = 0;
    DLL nums;
};

//MAke a constructor for zero polynomial as well as other polynomials
#endif //POLYNOMIAL_H


//
// Created by William on 3/13/2018.
//

#include "Warrior.h"
#include "Noble.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

namespace WarriorCraft{

    Warrior::Warrior(const string &name, int strength) : name(name), strength(strength) , noble{nullptr}{}
    int Warrior::getStrength()const {
        return strength;
    }
    void Warrior::damage(double damage) {
        strength -= damage;
    }
    string Warrior::getName() const {
        return name;
    }
    bool Warrior::isHired() const {
        if (noble == nullptr) {
            return false;
        }
        else{
            return true;
        }
    }
    bool Warrior::getHired(Noble& n) {
        if(noble != nullptr){
            return false;
        }
        else{
            noble = &n;
            return true;
        }
    }
    void Warrior::getFired(){
        noble = nullptr;
        return;
    }
    bool Warrior::runaway(){
        if(noble == nullptr) {
            return false;
        }
        else {
            cout << name << " flees in terror, abandoning his lord, " << noble->getName() << endl;
            int index = noble -> findWarrior(*this);
            noble -> removeWarrior(*this, index);
            noble = nullptr;
            return true;
        }
    }

    ostream& operator<<(ostream& os, const Warrior& w){
        os << "     " << w.name << ": " << w.strength << endl;
        return os;
    }
};
//output operator as a function here
//Functions like bool Noble::getAlive();

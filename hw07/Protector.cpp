hw07//
// Created by William on 4/6/2018.
//

#include "Noble.h"
#include "Protector.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

namespace WarriorCraft{
    Protector::Protector(const std::string &name, double strength) : name(name), strength(strength){}
    const string Protector::getName()const{
        return name;
    }

    double Protector::getStrength()const{
        return strength;
    }

    void Protector::damage(double damage) {
        strength -= damage;
    }

    bool Protector::isAlive()const{
        return alive;
    }
    void Protector::quit() {
        if(lord != nullptr){
            lord -> removeProtector(*this);
            lord = nullptr;
        }
    }

    bool Protector::isHired() const {
        return (lord != nullptr);
    }

    void Protector::getFired() {
        lord = nullptr;
    }

    bool Protector::getHired(Lord &l) {
        if(lord != nullptr){
            return false;
        }
        else{
            lord = &l;
            return true;
        }

    }

    Warrior::Warrior(const std::string &name, double strength) : Protector(name, strength) {}
    Wizard::Wizard(const std::string &name, double strength) : Protector(name, strength){}

    Archer::Archer(const std::string &name, double strength) : Warrior(name, strength){}
    Swordsman::Swordsman(const std::string &name, double strength) : Warrior(name, strength){}

    void Wizard::battlecry() const { cout << "POOF" << endl; }
    void Archer::battlecry() const {
        cout << "TWANG! " << name << " says: Take that in the name of my lord, " << lord -> getName() << endl;
    }
    void Swordsman::battlecry() const {
        cout << "CLANG! " << name << " says: Take that in the name of my lord, " << lord -> getName() << endl;
    }


}

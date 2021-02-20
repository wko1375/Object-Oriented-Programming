//
// Created by William on 4/6/2018.
//

#include "Noble.h"
#include "Protector.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

namespace WarriorCraft{
    Noble::Noble(std::string name) : name(name){}
    const string Noble::getName() const {
        return name;
    }
    bool Noble::alive() {
        return isAlive;
    }
    bool Noble::kill(){
        isAlive = false;
    }
    PersonWithStrengthToFight::PersonWithStrengthToFight(std::string name, double strength) : Noble(name), strength(strength){}
    string PersonWithStrengthToFight::getName() const {
        return name;
    }
    double PersonWithStrengthToFight::getStrength() const {
        return strength;
    }
    void PersonWithStrengthToFight::damage(double damage) {
        strength -= damage;
    }
    Lord::Lord(std::string name) : Noble(name){}
    bool Lord::hires(Protector& protector) {
        if(protector.isHired() || !protector.isAlive()){
            return false;
        }
        if(!isAlive){
            return false;
        }

        protector.getHired(*this);
        Protector* pptr = &protector;
        protectors.push_back(pptr);
        return true;
    }
    bool Lord::fire(Protector& protector){
        int index = findProtector(protector);
        if(!isAlive || !protector.isHired() || index == -1){
            return false;
        }
        else{
            protector.getFired();
            removeProtector(protector);
            return true;
        }
    }
    int Lord::findProtector(Protector& p){
        for(size_t i = 0; i < protectors.size(); i++){
            if(protectors[i] = &p){
                return i;
            }
        }
        return -1;
    }
    void Lord::removeProtector(Protector &p) {
        for(size_t i = 0; i < protectors.size(); i++){
            if(protectors[i] = &p){
                protectors[i] = protectors[protectors.size()];
                protectors.pop_back();
                return;
            }
        }
    }
    void Lord::battle(Lord& n) {
        double oStrength = 0;
        double mStrength = 0;
        cout << name << " battles " << n.getName() << endl;
        if (!isAlive && n.alive()) {
            cout << "He's dead " << n.getName() << endl;
            return;
        }
        if (!isAlive && !n.alive()) {
            cout << "Oh, NO! They're both Dead! Yuck!" << endl;
            return;
        }
        if (isAlive && !n.alive()) {
            cout << "He's dead, " << name << endl;
            return;
        }
        for (size_t i = 0; i < protectors.size(); i++) {
            mStrength += protectors[i]->getStrength();
            if(protectors[i] -> getStrength() != 0){
                protectors[i] -> battlecry();
            }
        }
        for (size_t i = 0; i < n.protectors.size(); i++) {
            oStrength += n.protectors[i]->getStrength();
            if(protectors[i] -> getStrength() != 0){
                protectors[i] -> battlecry();
            }
        }
        if (mStrength == oStrength) {
            cout << "Mutual Annihilation, " << name << " and " << n.name << " die at each other's hands." << endl;
            for (size_t i = 0; i < n.protectors.size(); i++) {
                n.protectors[i] -> damage(n.protectors[i]->getStrength());
            }
            for (size_t i = 0; i < protectors.size(); i++) {
                protectors[i] -> damage(protectors[i]->getStrength());
            }
            isAlive = false;
            n.isAlive = false;
            return;
        }
        if (mStrength > oStrength) {
            cout << name << " defeats " << n.name << endl;
            double ratio = oStrength / mStrength;
            for (size_t i = 0; i < n.protectors.size(); i++) {
                n.protectors[i]->damage(n.protectors[i]->getStrength());
            }
            for (size_t i = 0; i < protectors.size(); i++) {
                protectors[i] -> damage(ratio * protectors[i]->getStrength());
            }
            n.isAlive = false;
            return;
        }
        if (mStrength < oStrength) {
            cout << name << " is defeated by " << n.name << endl;
            double ratio = mStrength / oStrength;
            for (size_t i = 0; i < n .protectors.size(); i++) {
                n.protectors[i]->damage(ratio * n.protectors[i]->getStrength());
            }
            for (size_t i = 0; i < protectors.size(); i++) {
                protectors[i] -> damage(protectors[i]->getStrength());
            }
            isAlive = false;
            return;
        }
    }
    void Lord::battle(PersonWithStrengthToFight& n) {
        double oStrength = n.getStrength();
        double mStrength = 0;
        cout << name << " battles " << n.getName() << endl;
        for (size_t i = 0; i < protectors.size(); i++) {
            mStrength += protectors[i]->getStrength();
            if(protectors[i] -> getStrength() != 0){
                protectors[i] -> battlecry();
            }
        }
        if (!isAlive && n.alive()) {
            cout << "He's dead " << n.getName() << endl;
            return;
        }
        if (!isAlive && !n.alive()) {
            cout << "Oh, NO! They're both Dead! Yuck!" << endl;
            return;
        }
        if (isAlive && !n.alive()) {
            cout << "He's dead, " << name << endl;
            return;
        }

        if (mStrength == oStrength) {
            cout << "Mutual Annihilation, " << name << " and " << n.getName() << " die at each other's hands." << endl;
            for (size_t i = 0; i < protectors.size(); i++) {
                protectors[i] -> damage(protectors[i]->getStrength());
            }
            n.damage(oStrength);
            isAlive = false;
            n.kill();
            return;
        }
        if (mStrength > oStrength) {
            cout << name << " defeats " << n.getName() << endl;
            double ratio = oStrength / mStrength;
            for (size_t i = 0; i < protectors.size(); i++) {
                protectors[i] -> damage(ratio * protectors[i]->getStrength());
            }
            n.damage(oStrength);
            n.kill();
            return;
        }
        if (mStrength < oStrength) {
            cout << n.getName() << " defeats " << name << endl;
            for (size_t i = 0; i < protectors.size(); i++) {
                protectors[i] -> damage(protectors[i]->getStrength());
            }
            n.damage(mStrength);
            isAlive = false;
            return;
        }
    }
    void PersonWithStrengthToFight::battle(PersonWithStrengthToFight& n) {
        double oStrength = n.getStrength();
        double mStrength = strength;
        if (!isAlive && n.alive()) {
            cout << "He's dead " << n.getName() << endl;
            return;
        }
        if (!isAlive && !n.alive()) {
            cout << "Oh, NO! They're both Dead! Yuck!" << endl;
            return;
        }
        if (isAlive && !n.alive()) {
            cout << "He's dead, " << name << endl;
            return;
        }

        if (mStrength == oStrength) {
            cout << "Mutual Annihilation, " << name << " and " << n.getName() << " die at each other's hands." << endl;
            n.damage(oStrength);
            strength = 0;
            isAlive = false;
            n.kill();
            return;
        }
        if (mStrength > oStrength) {
            cout << name << " defeats " << n.getName() << endl;
            n.damage(oStrength);
            n.kill();
            strength -= oStrength;
            return;
        }
        if (mStrength < oStrength) {
            cout << n.getName() << " defeats " << name << endl;
            n.damage(mStrength);
            strength = 0;
            isAlive = false;
            return;
        }
    }
    void PersonWithStrengthToFight::battle(Lord& n) {
        double oStrength = 0;
        double mStrength = strength;
        cout << name << " battles " << n.getName() << endl;
        for (size_t i = 0; i < n.protectors.size(); i++) {
            mStrength += n.protectors[i]->getStrength();
            if(n.protectors[i] -> getStrength() != 0){
                n.protectors[i] -> battlecry();
            }
        }
        if (!isAlive && n.alive()) {
            cout << "He's dead " << n.getName() << endl;
            return;
        }
        if (!isAlive && !n.alive()) {
            cout << "Oh, NO! They're both Dead! Yuck!" << endl;
            return;
        }
        if (isAlive && !n.alive()) {
            cout << "He's dead, " << name << endl;
            return;
        }

        if (mStrength == oStrength) {
            cout << "Mutual Annihilation, " << name << " and " << n.getName() << " die at each other's hands." << endl;
            for (size_t i = 0; i < n.protectors.size(); i++) {
                n.protectors[i] -> damage(n.protectors[i]->getStrength());
            }
            strength = 0;
            isAlive = false;
            n.kill();
            return;
        }
        if (mStrength > oStrength) {
            cout << name << " defeats " << n.getName() << endl;
            for (size_t i = 0; i < n.protectors.size(); i++) {
                n.protectors[i] -> damage(n.protectors[i]->getStrength());
            }
            strength -= oStrength;
            n.kill();
            return;
        }
        if (mStrength < oStrength) {
            cout << n.getName() << " defeats " << name << endl;
            double ratio = mStrength/oStrength;
            for (size_t i = 0; i < n.protectors.size(); i++) {
                n.protectors[i] -> damage(ratio*n.protectors[i]->getStrength());
            }
            strength -= oStrength;
            isAlive = false;
            return;
        }
    }
}

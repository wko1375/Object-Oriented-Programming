//
// Created by William on 3/13/2018.
//

#include "Warrior.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;


namespace WarriorCraft{
    Noble::Noble(const string& nobleName) : name(nobleName){}
    Noble::Noble(const Noble& n){
        name = n.name;
        isAlive = n.isAlive;
        for(size_t i = 0; i < n.warriors.size(); i++) {
            Warrior *wptr = n.warriors[i];
            warriors.push_back(wptr);
        }
    }
    int Noble::findWarrior( Warrior &w) {
        for(size_t i = 0; i < warriors.size(); i++){
            if(warriors[i] -> getName() == w.getName()){
                return i;
            }
        }
        return -1;
   }
    bool Noble::hire(Warrior &w) {
        if(w.isHired()){
            return false;
        }
        if(!isAlive){
            return false;
        }
        else{
            Warrior* wptr = &w;
            warriors.push_back(wptr);
            w.getHired(*this);
            return true;
        }
    }
    bool Noble::fire(Warrior& w){
        int wIndex = findWarrior(w);
        if(!isAlive || !w.isHired()){
            return false;
        }
        else{
            w.getFired();
            removeWarrior(w, wIndex);
            return true;
        }
    }
    void Noble::battle(Noble &n) {
        double oStrength = 0;
        double mStrength = 0;
        cout << name << " battles " << n.name << endl;
        if (!isAlive && n.isAlive) {
            cout << name << " is dead, so he cannot battle." << endl;
            return;
        }
        if (!isAlive && !n.isAlive) {
            cout << "Oh, NO! They're both Dead! Yuck!" << endl;
            return;
        }
        if (isAlive && !n.isAlive) {
            cout << "He's dead, " << name << endl;
            return;
        }
        for (size_t i = 0; i < warriors.size(); i++) {
            mStrength += warriors[i]->getStrength();
        }
        for (size_t i = 0; i < n.warriors.size(); i++) {
            oStrength += n.warriors[i]->getStrength();
        }
        if (mStrength == oStrength) {
            cout << "Mutual Annihilation, " << name << " and " << n.name << " die at each other's hands." << endl;
            for (size_t i = 0; i < n.warriors.size(); i++) {
                n.warriors[i]->damage(n.warriors[i]->getStrength());
            }
            for (size_t i = 0; i < warriors.size(); i++) {
                warriors[i]->damage(warriors[i]->getStrength());
            }
            isAlive = false;
            n.isAlive = false;
            return;
        }
        if (mStrength > oStrength) {
            cout << name << " defeats " << n.name << endl;
            double ratio = oStrength / mStrength;
            for (size_t i = 0; i < n.warriors.size(); i++) {
                n.warriors[i]->damage(n.warriors[i]->getStrength());
            }
            for (size_t i = 0; i < warriors.size(); i++) {
                warriors[i]->damage(ratio * warriors[i]->getStrength());
            }
            n.isAlive = false;
            return;
        }
        if (mStrength < oStrength) {
            cout << name << " is defeated by " << n.name << endl;
            double ratio = mStrength / oStrength;
            for (size_t i = 0; i < n.warriors.size(); i++) {
                n.warriors[i]->damage(ratio * n.warriors[i]->getStrength());
            }
            for (size_t i = 0; i < warriors.size(); i++) {
                warriors[i]->damage(warriors[i]->getStrength());
            }
            isAlive = false;
            return;
        }
    }
    string Noble::getName() const {
        return name;
    }
    void Noble::removeWarrior(Warrior& w, int index){
        warriors[index], warriors[warriors.size()] = warriors[warriors.size()], warriors[index];
        warriors.pop_back();
        return;
    }
    ostream& operator<<(ostream& os, const Noble& n){
        os << n.name << " has an army of " << n.warriors.size() << ":" << endl;
        for(int i = 0; i < n.warriors.size(); i++){
            cout << *n.warriors[i];
        }
        return os;
    }
}

//Functions of warriors that are like int Warrior::getStrength(){}

//
// Created by William on 3/13/2018.
//

#ifndef NOBLE_H
#define NOBLE_H

#include "Warrior.h"
#include <string>
#include <vector>

namespace WarriorCraft{
    class Warrior;
    class Noble {
        friend std::ostream& operator<<(std::ostream& os, const Noble& n);
    public:
        Noble(const std::string& nobleName);
        Noble(const Noble& n);
        int findWarrior(Warrior& w);
        bool hire(Warrior& w);
        bool fire(Warrior& w);
        void battle(Noble& n);
        std::string getName()const;
        void removeWarrior(Warrior& w, int index);
    private:
        std::string name;
        std::vector<Warrior*> warriors;
        bool isAlive = true;
    };
}



#endif //UNTITLED2_NOBLE_H

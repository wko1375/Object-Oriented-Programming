//
// Created by William on 3/13/2018.
//

#ifndef WARRIOR_H
#define WARRIOR_H

#include "Noble.h"
#include <string>
#include <vector>

namespace WarriorCraft{

    class Noble;
    class Warrior {
        friend std::ostream& operator<<(std::ostream& os, const Warrior& w);
    public:
        Warrior(const std::string &name, int strength);
        int getStrength()const;
        void damage(double damage);
        bool isHired()const;
        bool getHired(Noble& n);
        bool runaway();
        void getFired();
        std::string getName()const;
    private:
        int strength;
        std::string name;
        Noble* noble = nullptr;
    };
}

#endif //UNTITLED2_WARRIOR_H

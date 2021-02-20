//
// Created by William on 4/6/2018.
//


#ifndef NOBLE_H
#define NOBLE_H
#include "Protector.h"
#include <string>
#include <vector>
#include <iostream>

namespace WarriorCraft{
    class Protector;
    class Archer;
    class Wizard;
    class Warrior;
    class Swordsman;

    class Noble{
    public:
        Noble(const std::string name);
        const std::string getName()const;
        bool alive();
        bool kill();
    protected:
        const std::string name;
        bool isAlive = true;
    private:
    };

    class PersonWithStrengthToFight : public Noble{
        friend class Lord;
    public:
        PersonWithStrengthToFight(std::string name, double strength);
        void battle(PersonWithStrengthToFight& n);
        void battle(Lord& n);
        double getStrength()const;
        void damage(double damage);
        std::string getName()const;

    private:
        double strength;
    };

    class Lord : public Noble{
        friend class PersonWithStrengthToFight;
    public:
        Lord(std::string name);
        void battle(Lord& n);
        void battle(PersonWithStrengthToFight& n);
        bool hires(Protector& protector);
        bool fire(Protector& protector);
        int findProtector(Protector& p);
        void removeProtector(Protector& p);
    private:
        std::vector<Protector*> protectors;
    };
    std::ostream& operator<<(std::ostream& os, const Noble& n);
}





#endif //HW07_NOBLE_H

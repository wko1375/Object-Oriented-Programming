r.h//
// Created by William on 4/6/2018.
//

#ifndef PROTECTOR_H
#define PROTECTOR_H
#include "Noble.h"
#include <string>
#include <vector>
#include <iostream>

namespace WarriorCraft{
    class Noble;
    class Lord;
    class PersonWithStrengthToFight;

    class Protector{
    public:
        Protector(const std::string& name, double strength);
        virtual void battlecry()const = 0;
        const std::string getName()const;
        double getStrength()const;
        void quit();
        bool isHired()const;
        bool getHired(Lord& l);
        void getFired();
        bool runaway();
        void damage(double damage);
        bool isAlive()const;
    protected:
        Lord* lord = nullptr;
        const std::string& name;
        double strength;
        bool alive = true;
    private:
    };

    class Warrior : public Protector{
    public:
        Warrior(const std::string& name, double strength);
    private:
    };

    class Wizard : public Protector{
    public:
        Wizard(const std::string& name, double strength);
        void battlecry()const;
    private:
    };

    class Archer : public Warrior{
    public:
        Archer(const std::string& name, double strength);
        void battlecry()const;
    private:
    };

    class Swordsman : public Warrior{
    public:
        Swordsman(const std::string& name, double strength);
        void battlecry()const;
    private:
    };


}



#endif //PROTECTOR_H

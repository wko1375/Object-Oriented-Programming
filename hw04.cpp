#include <iostream>
#include <string>
#include <vector>
using namespace std;



class Warrior{
public:
	Warrior(const string& name, int strength): name(name), strength(strength), hasEmployer(false){}
	string getName()const{
		return name;
	}
	int getStrength()const{
		return strength;
	}
	void damage(int damage){
		strength -= damage;
	}
	void display()const{
		cout << name << ": " << strength << endl;
	}
	bool hasNoble()const{
		return hasEmployer;
	}
	void setNoble(bool employer){
		hasEmployer = employer;
	}
private:
	int strength;
	bool hasEmployer;
	string name;
};



class Noble{
friend class Warrior;
public:
	Noble(const string& name): name(name), isAlive(true){}
	void display()const{
		cout << name << " has an army of " << warriors.size() << endl;
		for(int i = 0; i < warriors.size(); i++){
			cout << "     " << warriors[i]->getName() << ": " << warriors[i]->getStrength() << endl;
		}
	}
	void hire(Warrior w){
		if(!isAlive){
			cout << name << " is dead, he cannot hire anybody." << endl;
			return;
		}
		if(w.hasNoble()){
			cout << w.getName() << " already has an employer." << endl;
			return;
		}
		else{
			Warrior* wptr = &w;
			warriors.push_back(wptr);
			wptr->setNoble(true);
		}
	}
	void fire(Warrior w){
		if(isAlive){
			for(int i = 0; i < warriors.size(); i++){
				if(warriors[i]->getName() == w.getName()){
					cout << w.getName() << " you're fired!" << " -- " << name << endl;
					w.setNoble(false);
					for(int j = i; j < warriors.size(); j++){
						warriors[j], warriors[j+1] = warriors[j+1], warriors[j];
					}
					warriors.pop_back();
					return;
				}
			}
		}
		else{
			cout << name << " is dead, he cannot fire anybody." << endl;
			return;
		}
	}
	void battle(Noble n){
		int ownStrength = 0;
		int otherStrength = 0;
		cout << name << " battles " << n.name << endl;
		for(int i = 0; i < warriors.size(); i++){
			ownStrength += warriors[i]->getStrength();
		}
		for(int i = 0; i < n.warriors.size(); i++){
			otherStrength += n.warriors[i]->getStrength();
		}
		if(ownStrength == 0 && otherStrength == 0){
			cout << "Oh, NO! They're both dead! Yuck!" << endl;
			return;
		}
		if(ownStrength == 0){
			cout << name << " is dead, so he cannot battle." << endl;
			return;
		}
		if(otherStrength == 0){
			cout << "He's dead, " << name << endl;
			return;
		}
		if(ownStrength > otherStrength){
			cout << name << " defeats " << n.name << endl;
			int ratio = int(otherStrength/ownStrength);
			for(int i = 0; i < warriors.size(); i++){
				warriors[i]->damage(ratio);
			}
			for(int i = 0; i < n.warriors.size(); i++){
				n.warriors[i]->damage(n.warriors[i]->getStrength());
			}
			n.setAlive(false);
			return;
		}
		if(ownStrength < otherStrength){
			cout << name << " is defeated by " << n.name << endl;
			int ratio = ownStrength / otherStrength;
			for(int i = 0; i < n.warriors.size(); i++){
				n.warriors[i]->damage(n.warriors[i]->getStrength());
			}
			for(int i = 0; i < warriors.size(); i++){
				warriors[i]->damage(warriors[i]->getStrength());
			}
			isAlive = false;
			return;
		}
		if(ownStrength == otherStrength){
			cout << "Mutual Annihilation: " << name << " and " << n.name << " die at each other's hands." << endl;
			for(int i = 0; i < warriors.size(); i++){
				warriors[i]->damage(warriors[i]->getStrength());
			}
			for(int i = 0; i < n.warriors.size(); i++){
				n.warriors[i]->damage(n.warriors[i]->getStrength());
			}
			n.setAlive(false);
			return;
		}
	}
	void setAlive(bool life){
		isAlive = life;
	}
private:
	vector<Warrior*> warriors;
	string name;
	bool isAlive;
};


int main(){
	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");

	Warrior cheetah("Tarzan", 10);
	Warrior wizard("Merlin", 15);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);
	Warrior herb("Herb", 10);
	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(wizard);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(cheetah);

	jim.display();
	lance.display();
	art.display();
	linus.display();
	billie.display();

	art.fire(cheetah);
	art.display();

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);
}

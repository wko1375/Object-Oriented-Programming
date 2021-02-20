/*
William Ko
N15031967 wk700
Professor Sterling
hw05
This program reads through a file of commands, including "Noble", "Warrior", "Battle", "Hire", "Fire", "Status", and "Clear"
It executes the file based on what list of commands it reads, and outputs accordingly
*/

#include <iostream>
#include <fstream>
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
	Noble(const Noble& noble): name(noble.name), isAlive(noble.isAlive){
		for(int i = 0; i < noble.warriors.size(); i++){
			Warrior* wptr = new Warrior(*noble.warriors[i]);
			warriors.push_back(wptr);
		}
	}
	void hire(Warrior& w){
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
			w.setNoble(true);
		}
	}
	void fire(Warrior& w){
		if(isAlive){
			for(int i = 0; i < warriors.size(); i++){
				if(warriors[i]->getName() == w.getName()){
					cout << "You don't work for me anymore " << w.getName() << " -- " << name << endl;
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
	void battle(Noble& n){
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
			double ratio = (double)(otherStrength)/(double)(ownStrength);
			for(int i = 0; i < warriors.size(); i++){
				warriors[i]->damage(ratio*ownStrength);
			}
			for(int i = 0; i < n.warriors.size(); i++){
				n.warriors[i]->damage(n.warriors[i]->getStrength());
			}
			n.setAlive(false);
			return;
		}
		if(ownStrength < otherStrength){
			cout << name << " is defeated by " << n.name << endl;
			double ratio = (double)(ownStrength)/(double)(otherStrength);
			for(int i = 0; i < n.warriors.size(); i++){
				n.warriors[i]->damage(n.warriors[i]->getStrength()*ratio);
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
	string getName()const{
		return name;
	}
private:
	vector<Warrior*> warriors;
	string name;
	bool isAlive;
};

int checkExistingNoble(string name, const vector<Noble*> nobles);
int checkExistingWarrior(const string& name, const vector<Warrior*> warriors);
void clearAll(vector<Noble*>& n, vector<Warrior*>& w);

int main(){
	ifstream battlefield("nobleWarriors.txt");
	if(!battlefield){
		cerr << "File couldn't be opened." << endl;
		exit(1);
	}
	vector<Noble*> nobles;
	vector<Warrior*> ws;
	string command;
	while(battlefield >> command){
		if(command == "Noble"){
			string nobleName;
			battlefield >> nobleName;
			if(checkExistingNoble(nobleName, nobles) != -1){
				cout << "There is an existing Noble with this name." << endl;
				continue;
			}
			else{
				Noble* nptr = new Noble(nobleName);
				nobles.push_back(nptr);
				continue;
			}
		}
		if(command == "Warrior"){
			string warriorName;
			int strength;
			battlefield >> warriorName >> strength;
			if(checkExistingWarrior(warriorName, ws) != -1){
				cout << "There is an existing Warrior with this name." << endl;
				continue;
			}
			else{
				Warrior* wptr = new Warrior(warriorName, strength);
				ws.push_back(wptr);
				continue;
			}
		}
		if(command == "Status"){
			cout << "Status" << endl;
			cout << "-----" << endl;
			cout << "Nobles: " << endl;
			if(nobles.size() == 0){
				cout << "NONE" << endl;
			}
			else{
				for(int i = 0; i < nobles.size(); i++){
					nobles[i] -> display();
				}
			}
			cout << "Unemployed Warriors: " << endl;
			int employedCount = 0;
			for(int i = 0; i < ws.size(); i++){
				if(!ws[i] -> hasNoble()){
					ws[i] -> display();
				}
				else{
					employedCount += 1;
				}
			}
			if(employedCount == ws.size()){
				cout << "NONE" << endl;
			}
		}
		if(command == "Hire"){
			string nobleName;
			string warriorName;
			int nobleIndex = -1;
			int warriorIndex = -1;
			battlefield >> nobleName >> warriorName;
			for(int i = 0; i < nobles.size(); i++){
				if(nobles[i] -> getName() == nobleName){
					nobleIndex = i;
				}
			}
			for(int i = 0; i < ws.size(); i++){
				if(ws[i] -> getName() == warriorName){
					warriorIndex = i;
				}
			}
			if(nobleIndex != -1 && warriorIndex != -1){
				nobles[nobleIndex] -> hire(*ws[warriorIndex]);
				continue;
			}
			else{
				if(nobleIndex == -1){
					cout << "There is no Noble by that name." << endl;
					continue;
				}
				if(warriorIndex == -1){
					cout << "There is no Warrior by that name." << endl;
					continue;
				}
			}
		}
		if(command == "Fire"){
			string nobleName;
			string warriorName;
			battlefield >> nobleName >> warriorName;
			int nobleIndex = checkExistingNoble(nobleName, nobles);
			int warriorIndex = checkExistingWarrior(warriorName, ws);
			if(nobleIndex != -1 && warriorIndex != -1){
				nobles[nobleIndex] -> fire(*ws[warriorIndex]);
				continue;
			}
			else{
				if(nobleIndex == -1){
					cout << "There is no Noble by that name." << endl;
				}
				if(warriorIndex == -1){
					cout << "There is no Warrior by that name." << endl;
					continue;
				}
				continue;
			}
		}
		if(command == "Battle"){
			string firstNobleName;
			string secondNobleName;
			battlefield >> firstNobleName >> secondNobleName;
			int firstNobleIndex = checkExistingNoble(firstNobleName, nobles);
			int secondNobleIndex = checkExistingNoble(secondNobleName, nobles);
			if(firstNobleIndex == -1){
				if(secondNobleIndex == -1){
					cout << "Both of these Nobles do not exist..." << endl;
					continue;
				}
				cout << firstNobleName << " doesn't exist..." << endl;
				continue;
			}
			if(secondNobleIndex == -1){
				cout << secondNobleName << " doesn't exist..." << endl;
				continue;
			}
			else{
				nobles[firstNobleIndex] -> battle(*nobles[secondNobleIndex]);
				continue;

			}
		}
		if(command == "Clear"){
			clearAll(nobles, ws);
		}
	}
}


//Checks if noble with name name exists already in the battlefield - returns -1 if it doesn't, and returns the index of the noble if it does
int checkExistingNoble(string name, const vector<Noble*> nobles){
	for(int i = 0; i < nobles.size(); i++){
		if(nobles[i] -> getName() == name){
			return i;
		}
	}
	return -1;
}

//Checks if warrior with name name exists already in the battlefield - returns -1 if it doesn't, and returns the index of the warrior if it does
int checkExistingWarrior(const string& name, const vector<Warrior*> warriors){
	for(int i = 0; i < warriors.size(); i++){
		if(warriors[i] -> getName() == name){
			return i;
		}
	}
	return -1;
}

//Deletes all nobles and warriors within the battlefield
void clearAll(vector<Noble*>& n, vector<Warrior*>& w){
	for(int i = 0; i < w.size(); i++){
		delete w[i];
	}
	w.clear();
	for(int i = 0; i < n.size(); i++){
		delete n[i];
	}
	n.clear();
}

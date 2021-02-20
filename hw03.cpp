/*
William Ko
N15031967
Professor Sterling
Hw#03
This program reads in a file and creates warriors, with fields name, weapon name, and weapon strength
If the program reads in "Status" it displays the number of warriors on the field and their fields
If the program reads in "Battle" it conducts a battle between two warrriors where the stronger one emerges victorious
*/



#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

//Function Prototypes
class Warrior;
void status(vector<Warrior>& w);
void battle(int i1, int i2, vector<Warrior>& w);
int find_warrior(string warrior_name, vector<Warrior>& warriors);
void execute_file(string filename);


int main(){
	execute_file("warriors.txt");
	return 0;
}

class Warrior{
public:
	friend class Weapon; //Allows Warrior to access variables of Weapon
	Warrior(const string& name, const string& weapon_name, int strength): w_name(name), W(weapon_name, strength){}
	void damage_weapon(int damage){
		W.strength -= damage;
	}
	string getname(){
		return w_name;
	}
	string get_weapon_name(){
		return W.get_weapon_name();
	}
	int get_weapon_strength(){
		return W.strength;
	}
private:
	string w_name;
	class Weapon{
	public:
		Weapon(const string& weapon_name, int strength): weapon_name(weapon_name), strength(strength){}
		int strength;
		string get_weapon_name(){
			return weapon_name;
		}
	private:
		string weapon_name;
	};
	Weapon W;
};

//Displays number of warriors, names, weapon names, and strengths
void status(vector<Warrior>& w){
	cout << "There are " << w.size() << " warriors." << endl;
	for(int i = 0; i < w.size(); i++){
		string name = w[i].getname();
		int strength = w[i].get_weapon_strength();
		string weapon_name = w[i].get_weapon_name();
		cout << "Warrior: " << name << ", weapon: " << weapon_name << ", " << strength << endl;
	}
}

//Conducts a battle between two warriors
void battle(int i1, int i2, vector<Warrior>& w){
	cout << w[i1].getname() << " battles " << w[i2].getname() << endl;
	if(w[i1].get_weapon_strength() == 0 && w[i2].get_weapon_strength() == 0){
		cout << "Oh, NO! They're both dead! Yuck!" << endl;
		return;
	}
	if(w[i1].get_weapon_strength() == 0 && w[i2].get_weapon_strength() != 0){
		cout << "He's dead, " << w[i2].getname() << endl;
		return;
	}
	if(w[i1].get_weapon_strength() != 0 && w[i2].get_weapon_strength() == 0){
		cout << "He's dead, " << w[i1].getname() << endl;
		return;
	}
	if(w[i1].get_weapon_strength() == w[i2].get_weapon_strength()){
		int w1_strength = w[i1].get_weapon_strength();
		int w2_strength = w[i2].get_weapon_strength();
		w[i1].damage_weapon(w2_strength);
		w[i2].damage_weapon(w1_strength);
		cout << "Mutual Annihilation: " << w[i1].getname() << " and " << w[i2].getname() << " die at each other's hands." << endl;
		return;
	}
	if(w[i1].get_weapon_strength() > w[i2].get_weapon_strength()){
		cout << w[i1].getname() << " defeats " << w[i2].getname() << endl;
		int w2_strength = w[i2].get_weapon_strength();
		w[i1].damage_weapon(w2_strength);
		w[i2].damage_weapon(w2_strength);
		return;
	}
	if(w[i1].get_weapon_strength() < w[i2].get_weapon_strength()){
		cout << w[i1].getname() << " is defeated by " << w[i2].getname() << endl;
		int w1_strength = w[i1].get_weapon_strength();
		w[i1].damage_weapon(w1_strength);
		w[i2].damage_weapon(w1_strength);
		return;

	}
}

// This function is used to find the index of the warrior with the name warrior_name in the vector of warriors
// It returns the integer that is the index
int find_warrior(string warrior_name, vector<Warrior>& warriors){
	for(int i = 0; i < warriors.size(); i++){
		if(warriors[i].getname() == warrior_name){
			return i;
		}
	}
}

void execute_file(string filename){
	ifstream w_file(filename);
	if(!w_file){
		cerr << "Couldn't open file" << endl;
		exit(1);
	}

	vector<Warrior> warriors; //Vector where all warriors are stored
	string command;

	/*
	This loop takes in the command at the beginning of every line, and depending on what the command is, it either calls the
	battle function, status function, or warrior constructor. After a command has been done, there is a continue
	statement that goes to the next iteration of the loop, ensuring that each loops does one command only.
	*/

	while(w_file >> command){

		if(command == "Status"){
			status(warriors);
			continue;
		}

		if(command == "Battle"){
			string w_one;
			string w_two;
			w_file >> w_one >> w_two;
			battle(find_warrior(w_one, warriors), find_warrior(w_two, warriors), warriors);
			continue;
		}

		if(command == "Warrior"){
			string name;
			string weapon_name;
			int strength;
			w_file >> name >> weapon_name >> strength;
			warriors.push_back(Warrior(name, weapon_name, strength));
			continue;
		}
	}
	return;
}

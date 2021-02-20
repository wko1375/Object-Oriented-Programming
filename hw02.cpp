/*
William Ko
N15031967
Professor Sterling
Object Oriented Programming hw02

This program reads a file that contains a series of three commands: Warrior, Status, and Battle
The Warrior command creates a new Warrior
The Status command displays the strengths and names of all created warriors
The Battle command conducts a battle between two warriors, where the stronger one is victorious
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

//Struct and Function Prototypes
struct Warrior;
void status(const vector<Warrior>& warriors);
void battle(int i1, int i2, vector<Warrior>& w);
int find_warrior(string warrior_name, vector<Warrior>& warriors);
void execute_file(string filename);

int main(){
 	execute_file("warriors.txt");
	return 0;
}


//Structure for a Warrior
struct Warrior{
	string name;
	int strength;
};

//Passing by constant reference the vector of stored warriors
void status(const vector<Warrior>& warriors){
	cout << "There are: " << warriors.size() << " warriors" << endl;
	for(int i = 0; i < warriors.size(); i++){
		cout << "Warrior: " << warriors[i].name << ", strength: " << warriors[i].strength << endl;
	}
}

// Passing vector of warriors in by constant reference
// int i1 and i2 are the indices in the vector where the first and second warriors is stored
void battle(int i1, int i2, vector<Warrior>& w){
	cout << w[i1].name << " battles " << w[i2].name << endl;
	if(w[i1].strength == 0 && w[i2].strength == 0){
		cout << "Oh, NO! They're both dead! Yuck!" << endl;
		return;
	}
	if(w[i1].strength == 0 && w[i2].strength != 0){
		cout << "He's dead, " << w[i2].name << endl;
		return;
	}
	if(w[i1].strength != 0 && w[i2].strength == 0){
		cout << "He's dead, " << w[i1].name << endl;
		return;
	}
	if(w[i1].strength == w[i2].strength){
		w[i1].strength -= w[i1].strength;
		w[i2].strength -= w[i2].strength;
		cout << "Mutual Annihilation: " << w[i1].name << " and " << w[i2].name << " die at each other's hands." << endl;
		return;
	}
	if(w[i1].strength > w[i2].strength){
		cout << w[i1].name << " defeats " << w[i2].name << endl;
		w[i1].strength -= w[i2].strength;
		w[i2].strength -= w[i2].strength;
		return;
	}
	if(w[i1].strength < w[i2].strength){
		cout << w[i1].name << " is defeated by " << w[i2].name << endl;
		w[i1].strength -= w[i1].strength;
		w[i2].strength -= w[i1].strength;
		return;
	}
}

// This function is used to find the index of the warrior with the name warrior_name in the vector of warriors
// It returns the integer that is the index
int find_warrior(string warrior_name, vector<Warrior>& warriors){
	for(int i = 0; i < warriors.size(); i++){
		if(warriors[i].name == warrior_name){
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
			Warrior aWarrior;
			w_file >> aWarrior.name >> aWarrior.strength;
			warriors.push_back(aWarrior);
			continue;
		}

	}
	return;
}

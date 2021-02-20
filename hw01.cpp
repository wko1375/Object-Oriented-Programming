/*
CS-UY 2124
John Sterling
William Ko
N15031967
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
int loop = 26; //Integer that loops decrypted_char back if it goes out of bounds

char decrypt_char(char chr, int rotation) {
	if (chr >= 'a' && chr <= 'z') {
		chr -= rotation;
		if (chr < 'a') {
			chr += loop;
		}
		return chr;
	}
	else {
		return chr;
	}
}

void decrypt_string(string& str, int rotation) {
	string decrypted_string;
	int string_size = str.size();
	for (int i = 0; i < string_size; i++) {
		char decrypted_char = decrypt_char(str[i], rotation); //Decrypts each individual char in the string
		decrypted_string += decrypted_char; //Adds each decrypted char to a new string object
	}
	str = decrypted_string; //Sets reference of initial string to the new decrypted string
}

vector<string> decrypt_filelines(string filename, int rotation) {
	vector<string> decrypted_filelines;
	ifstream encrypted_file(filename);
	if (!encrypted_file) {
		cerr << "Couldn't open file!" << endl;
		exit(1);
	}
	string next_line;
	while (getline(encrypted_file, next_line)) { //Decrypts line in the file
		decrypt_string(next_line, rotation);
		decrypted_filelines.push_back(next_line); //Adds decrypted line to a vector
	}
	encrypted_file.close();
	return decrypted_filelines;
}

int get_rotation(string filename) { //Retrieves number of letters file is supposed to be rotated
	ifstream file_name(filename);
	if (!file_name) {
		cerr << "Couldn't open file!" << endl;
		exit(1);
	}
	string first_line;
	int rotation;
	int rotation_int;
	while (file_name >> rotation_int) {
		rotation = rotation_int;
	}
	file_name.close();
	return rotation;
}
	


int main() {
	int rotation = get_rotation("encrypted.txt");
	cout << rotation << endl;
	vector<string> decrypted_filelines = decrypt_filelines("encrypted.txt", rotation);
	for (int i = decrypted_filelines.size(); i > 1; i--) { //Prints all decrypted text, except the first line which is the rotation number
		cout << decrypted_filelines[i - 1] << endl;
	}
	return 0;
}

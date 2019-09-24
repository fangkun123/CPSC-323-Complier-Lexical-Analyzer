#include<iostream>
#include<fstream>
#include <iomanip>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

using namespace std;

char ch, buffer[15], operators[] = "*+-=/><%", separator[] = "(){}[],.:;! ";
bool hasSep = false;
int currentIndex = 0;

bool isKeyword(char buffer[]) {
	char keywords[18][10] = { "int", "float", "bool", "if", "else", "then", "endif", "while", "whileend", "do", "doend",
								"for", "forend", "input", "output", "and", "or", "function"};

	for (int i = 0; i < 18; ++i)
		if (strcmp(keywords[i], buffer) == 0)
			return true;

	return false;
}

bool isOperator(int index) {
	if (ch == operators[index])
		return true;
	else
		return false;
}

bool isSeparator(int index) {
	if (ch == separator[index])
		return true;
	else
		return false;
}

bool isReal(char buffer[]) {
	string str(buffer);
	string substr(".");

	size_t found = str.find(substr);

	if (found != string::npos) {
		for (int i = 0; i < found; i++) {
			if (!isdigit(buffer[i]))
				return false;
			continue;
		}
		for (int i = found + 1; i < currentIndex; i++) {
			if (!isdigit(buffer[i]))
				return false;
			continue;
		}
		return true;
	}
	else
		return false;
}

bool isNumber(char buffer[]) {
	for (int i = 0; i <= (currentIndex - 1); i++) {
		if (!isdigit(buffer[i]))
			return false;
		continue;
	}
	return true;
}



int main() {
	bool comment = false;
	char detection[2] = { ' ', ' ' };
	int x = 0;
	ifstream fin("program.txt");
	int j = 0;
	
	if (!fin.is_open()) {
		cout << "error while opening the file\n";
		exit(0);
	}
	cout << "TOKENS               Lexemes" << endl; //6

	while (!fin.eof()) {
		ch = fin.get();
	
		if (ch == '!') {
			detection[x] = ch;
			x++;
			if (detection[1] == ch) {
				comment = false;
				x = 0;
				detection[0] = ' ';
				detection[1] = ' ';
			}
			else
				comment = true;
		}
		if (!comment) {

			for (int i = 0; i < 12; ++i) {
				if (isSeparator(i)) {
					if (ch == '!') {
						continue;
					}
					else if (ch == ' ') {
						continue;
					}
					else if (ch == '.') {
						continue;
					}
					else {
						cout << "SEPARATOR       =     " << ch << endl;
						hasSep = true;
					}
				}
			}

			if (isalnum(ch) || ch == '$' || ch == '.') {
				buffer[j++] = ch;
				currentIndex++;
			}
			else if ((ch == ' ' || ch == '\n' || hasSep) && (j != 0)) {
				buffer[j] = '\0';
				j = 0;

				if (isKeyword(buffer))
					cout << "KEYWORD         =     " << buffer << endl;
				else if (isReal(buffer))
					cout << "REAL            =     " << buffer << endl;
				else if (isNumber(buffer))
					cout << "NUMBER          =     " << buffer << endl;
				else // isIdentifier
					cout << "INDENTIFIER     =     " << buffer << endl;

				currentIndex = 0;
				//if(hasSep){
			//		cout << "SEPARATOR       =     " << ch << endl;
			//	}
			}

			for (int i = 0; i < 8; ++i) {
				if (isOperator(i))
					cout << "OPERATOR        =     " << ch << endl; //8
			}
		}



	}

	fin.close();
	

	system("pause");
	return 0;
}
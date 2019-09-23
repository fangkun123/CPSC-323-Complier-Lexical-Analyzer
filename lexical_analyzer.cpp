#include<iostream>
#include<fstream>
#include <iomanip>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

using namespace std;

char ch, buffer[15], operators[] = "*+-=/><%", separator[] = "(){}[],.:;! ";

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




int main() {
	ifstream fin("program.txt");
	int j = 0;

	if (!fin.is_open()) {
		cout << "error while opening the file\n";
		exit(0);
	}
	cout << "TOKENS               Lexemes" << endl; //6

	while (!fin.eof()) {
		ch = fin.get();

		for (int i = 0; i < 6; ++i) {
			if (isOperator(i))
				cout << "OPERATOR        =     "<< ch << endl; //8
		}

		for (int i = 0; i < 12; ++i) {
			if (isSeparator(i)) {
				if (ch == '!') {
					continue;
				}
				else if (ch == ' ') {
					continue;
				}
				else
					cout << "SEPARATOR       =     " << ch << endl; // 9
			}
		}


		if (isalnum(ch) || ch == '$') {
			buffer[j++] = ch;
		}
		else if ((ch == ' ' || ch == '\n') && (j != 0)) {
			buffer[j] = '\0';
			j = 0;

			if (isKeyword(buffer))
				cout << "KEYWORD         =     " << buffer << endl; //7
			else // isIdentifier
				cout << "INDENTIFIER     =     " << buffer << endl; //11
		}

	}

	fin.close();
	

	system("pause");
	return 0;
}
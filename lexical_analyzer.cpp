#include<iostream>
#include<fstream>
#include <iomanip>
#include <string>
#include <string.h>

using namespace std;

char operators[] = "*+-=/><%";
char separator[] = "'(){}[],:;";
char keywords[18][10] = { "int", "float", "bool", "if", "else", "then", "endif", "while", "whileend", "do", "doend","for", "forend", "input", "output", "and", "or", "function" };
bool hasSep = false;	// check if has separater
bool hasOpe = false;	// check if has operator
int currentIndex = 0;	// index for check isNumber() and isReal()

// FSM states for print
bool endOperator = false;
bool endSeparator = false;
bool endNumber = false;
bool endReal = false;
bool endIdentifier = false;

ifstream fin;		//read file
ofstream outputFile;
char ch;	// read file and get every character
char buffer[15];	//store characters in an array to determine isKeyword or isNumber or isReal or isIdentifier
int j = 0;		// index for buffer[]
bool isComments = false;	//check if it is comments
char detection[2] = { '\0' };	// detect '!' twice, if detect, add '!' to array according to occur times
int x = 0;	// used to counting detection array

bool isKeyword(char buffer[]) {
	for (int i = 0; i < 18; ++i)
		if (strcmp(keywords[i], buffer) == 0)
			return true;
	return false;
}

bool isOperator(char ch) {
	for (int i = 0; i < 10; ++i) {
		if (ch == operators[i])
			return true;
	}
	return false;	
}

bool isSeparator(char ch) {
	for (int i = 0; i < 10; ++i) {	//check separator
		if (ch == separator[i])
			return true;
	}
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

void print() {

	if (endIdentifier) {
		cout << "IDENTIFIER      =     " << buffer << endl;
		outputFile << "IDENTIFIER      =     " << buffer << endl;
		endIdentifier = false;
	}

	if (endNumber) {
		cout << "NUMBER          =     " << buffer << endl;
		outputFile << "NUMBER          =     " << buffer << endl;

		endNumber = false;
	}

	if (endReal) {
		cout << "REAL            =     " << buffer << endl;
		outputFile << "REAL            =     " << buffer << endl;
		endReal = false;
	}

	if (endSeparator) {	// single separator detected, print it
		cout << "SEPARATOR       =     " << ch << endl;
		outputFile << "SEPARATOR       =     " << ch << endl;
		endSeparator = false;
		hasSep = false;
	}
	if (endOperator) { // single operator detected, print it
		cout << "OPERATOR        =     " << ch << endl;
		outputFile << "OPERATOR        =     " << ch << endl;
		endOperator = false;
		hasOpe = false;
	}
}

void lexer() {

	if (ch == '!') {	//check if is comment
		detection[x] = ch;
		x++;
		if (detection[1] == ch) {
			isComments = false;
			x = 0;
			detection[0] = '\0';
			detection[1] = '\0';
		}
		else
			isComments = true;
	}
	if (!isComments) {	// if not comment, start lexical analyzer


		if (isSeparator(ch)) {
			hasSep = true;
			endSeparator = true;
		}

		if (isOperator(ch)) {
			hasOpe = true;
			endOperator = true;
		}

		if (isalnum(ch) || ch == '$' || ch == '.') {	// check ch is a number or letter or '$' or '.'
			buffer[j++] = ch;		// if so, add to buffer
			currentIndex++;
		}
		else if ((ch == ' ' || ch == '\n' || hasSep || hasOpe || fin.eof()) && (j != 0)) {	// end of variables by detecting if j(index for buffer[]) != 0
			buffer[j] = '\0';	// set last char in buffer( might be ' ', '\n', separator, operator
			j = 0;	// reset the index for buffer[]
			if (isKeyword(buffer)) {	// check if the variable is keyword
				cout << "KEYWORD         =     " << buffer << endl;
				outputFile << "KEYWORD         =     " << buffer << endl;
			}
			else if (isReal(buffer))	//check if the variable is real( number with '.')
				endReal = true;
			else if (isNumber(buffer)) //check if the variable is number 
				endNumber = true;
			else {	//check if the variable is identifier
				if (!isdigit(buffer[0]))	// check if identifier not start with number
					endIdentifier = true;
			}

			currentIndex = 0;	// reset index for isNumber() and isReal()
		}
		print();
	}
}


int main() {
	string filename, outputFileName;
	cout << "Please enter file name where you want to read: ";
	cin >> filename;

	cout << "Please enter file name where you want to store output: ";
	cin >> outputFileName;

	
	fin.open(filename);
	outputFile.open(outputFileName);

	if (!fin.is_open()) {
		cout << "error while opening the file\n";
		exit(0);
	}
	cout << "TOKENS               Lexemes" << endl; // print table contents
	outputFile << "TOKENS               Lexemes\n";

	while (!fin.eof()) {
		ch = fin.get();
		lexer();	// include print() in the function
	}

	fin.close();	//close file
	outputFile.close(); //close output file

	system("pause");
	return 0;
}
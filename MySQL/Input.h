#pragma once
// Name: Ba
// Date: 10/26/2022
// Description: Input header file
#pragma once
#include <iostream>
#include <vector>
std::string inputString(std::string prompt, bool spaces);
std::string inputString(std::string prompt, bool spaces, bool empty);
char inputChar(std::string prompt, char* list, const int SIZE);
char inputChar(std::string prompt, std::vector<char> list, const int SIZE);
char inputChar(std::string prompt, std::string options);
char inputChar(std::string prompt, char yes, char no);
char inputChar(std::string prompt, bool alphaOrDigit);
char inputChar(std::string prompt);
int inputInteger(std::string prompt);
int inputInteger(std::string prompt, bool posNeg);
int inputInteger(std::string prompt, int start, bool greater);
int inputInteger(std::string prompt, int startRange, int endRange);
double inputDouble(std::string prompt);
double inputDouble(std::string prompt, bool posNeg);
double inputDouble(std::string prompt, double start, bool posNeg);
double inputDouble(std::string prompt, double startRange, double endRange);

void cls();

// Precondition : Requires an existing String Object
// Postcondition: Returns a string that does not have any leading spaces
std::string& ltrim(std::string& str, std::string const& whitespace);
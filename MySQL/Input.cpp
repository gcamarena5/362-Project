#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <limits>
#include <sstream>
#include <cmath>
#include <cctype>
#include <cstdlib>
#include "Input.h"

using namespace std;

namespace {
    // Read one complete line. Returns false if the input stream has closed.
    bool readLine(const string& prompt, string& line) {
        cout << prompt;
        if (!getline(cin, line)) {
            if (cin.eof()) return false;
            cin.clear();
            return false;
        }
        return true;
    }

    string trimCopy(const string& value) {
        const string whitespace = " \r\n\t\v\f";
        const size_t first = value.find_first_not_of(whitespace);
        if (first == string::npos) return "";
        const size_t last = value.find_last_not_of(whitespace);
        return value.substr(first, last - first + 1);
    }

    bool parseIntLine(const string& line, int& value) {
        istringstream input(line);
        input >> value;
        if (input.fail()) return false;
        input >> ws;
        return input.eof(); // Reject inputs such as "12abc".
    }

    bool parseDoubleLine(const string& line, double& value) {
        istringstream input(line);
        input >> value;
        if (input.fail() || !isfinite(value)) return false;
        input >> ws;
        return input.eof(); // Reject inputs such as "2.5abc", NaN, and infinity.
    }

    void showCharacterOptions(const string& options) {
        cout << "Allowed options: ";
        for (size_t i = 0; i < options.size(); ++i) {
            if (i) cout << ", ";
            cout << '\'' << options[i] << '\'';
        }
        cout << ".\n";
    }
}

void cls() {
    system("cls");
}

char inputChar(string prompt, vector<char> list, const int SIZE) {
    string options;
    const int count = min(SIZE, static_cast<int>(list.size()));
    for (int i = 0; i < count; ++i) options += list[i];
    return inputChar(prompt, options);
}

char inputChar(string prompt, char* list, const int SIZE) {
    if (list == nullptr || SIZE <= 0) {
        cout << "ERROR: No valid character options were provided.\n";
        return '\0';
    }
    string options(list, list + SIZE);
    return inputChar(prompt, options);
}

char inputChar(string prompt, string options) {
    string line;
    while (true) {
        if (!readLine(prompt, line)) return '\0';
        line = trimCopy(line);
        if (line.size() == 1) {
            const char input = static_cast<char>(toupper(static_cast<unsigned char>(line[0])));
            for (char option : options) {
                if (input == toupper(static_cast<unsigned char>(option))) return input;
            }
        }
        cout << "ERROR: Enter exactly one character from the options.\n";
        showCharacterOptions(options);
    }
}

char inputChar(string prompt, char yes, char no) {
    string options;
    options += yes;
    if (toupper(static_cast<unsigned char>(yes)) != toupper(static_cast<unsigned char>(no)))
        options += no;
    return inputChar(prompt, options);
}

char inputChar(string prompt, bool alphaOrDigit) {
    string line;
    while (true) {
        if (!readLine(prompt, line)) return '\0';
        line = trimCopy(line);
        if (line.size() == 1) {
            const unsigned char ch = static_cast<unsigned char>(line[0]);
            if ((alphaOrDigit && isalpha(ch)) || (!alphaOrDigit && isdigit(ch)))
                return line[0];
        }
        cout << (alphaOrDigit
            ? "ERROR: Enter one alphabetic character.\n"
            : "ERROR: Enter one digit character.\n");
    }
}

// Accepts any single character; pressing Enter returns '\n'.
char inputChar(string prompt) {
    string line;
    if (!readLine(prompt, line)) return '\0';
    return line.empty() ? '\n' : static_cast<char>(toupper(static_cast<unsigned char>(line[0])));
}

string inputString(string prompt, bool spaces) {
    string line;
    while (true) {
        if (!readLine(prompt, line)) return "";
        if (!spaces) {
            istringstream input(line);
            string token;
            if (input >> token) return token;
            cout << "ERROR: Input cannot be empty.\n";
        } else {
            return line; // Preserve spaces inside a description/name.
        }
    }
}

string inputString(string prompt, bool spaces, bool empty) {
    if (empty) return inputString(prompt, spaces);

    string line;
    while (true) {
        if (!readLine(prompt, line)) return "";
        if (!trimCopy(line).empty()) {
            return spaces ? line : trimCopy(line).substr(0, trimCopy(line).find_first_of(" \t\r\n"));
        }
        cout << "ERROR: The string cannot be empty or whitespace-only.\n";
    }
}

int inputInteger(string prompt) {
    string line;
    int value;
    while (true) {
        if (!readLine(prompt, line)) return 0;
        if (parseIntLine(line, value)) return value;
        cout << "ERROR: Enter a valid whole number (for example, 12).\n";
    }
}

int inputInteger(string prompt, bool posNeg) {
    int value;
    while (true) {
        value = inputInteger(prompt);
        if (posNeg && value >= 0) return value;
        if (!posNeg && value <= 0) return value;
        cout << (posNeg ? "ERROR: Number must be zero or positive.\n"
                        : "ERROR: Number must be zero or negative.\n");
    }
}

int inputInteger(string prompt, int start, bool greater) {
    int value;
    while (true) {
        value = inputInteger(prompt);
        if ((greater && value >= start) || (!greater && value <= start)) return value;
        cout << "ERROR: Number must be "
             << (greater ? "at least " : "at most ") << start << ".\n";
    }
}

int inputInteger(string prompt, int startRange, int endRange) {
    const int low = min(startRange, endRange);
    const int high = max(startRange, endRange);
    int value;
    while (true) {
        value = inputInteger(prompt);
        if (value >= low && value <= high) return value;
        cout << "ERROR: Enter a number between " << low << " and " << high << ".\n";
    }
}

double inputDouble(string prompt) {
    string line;
    double value;
    while (true) {
        if (!readLine(prompt, line)) return 0.0;
        if (parseDoubleLine(line, value)) return value;
        cout << "ERROR: Enter a valid finite number (for example, 12.50).\n";
    }
}

double inputDouble(string prompt, bool posNeg) {
    double value;
    while (true) {
        value = inputDouble(prompt);
        if (posNeg && value >= 0.0) return value;
        if (!posNeg && value <= 0.0) return value;
        cout << (posNeg ? "ERROR: Number must be zero or positive.\n"
                        : "ERROR: Number must be zero or negative.\n");
    }
}

double inputDouble(string prompt, double start, bool posNeg) {
    double value;
    while (true) {
        value = inputDouble(prompt);
        if ((posNeg && value >= start) || (!posNeg && value <= start)) return value;
        cout << "ERROR: Number must be "
             << (posNeg ? "at least " : "at most ") << start << ".\n";
    }
}

double inputDouble(string prompt, double startRange, double endRange) {
    const double low = min(startRange, endRange);
    const double high = max(startRange, endRange);
    double value;
    while (true) {
        value = inputDouble(prompt);
        if (value >= low && value <= high) return value;
        cout << "ERROR: Enter a number between " << low << " and " << high << ".\n";
    }
}

string& ltrim(string& str, string const& whitespace) {
    const size_t first = str.find_first_not_of(whitespace);
    if (first == string::npos) str.clear();
    else str.erase(0, first);
    return str;
}

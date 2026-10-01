#include <iostream>
#include <vector>
#include <string>

using namespace std;
#include "Database_V.h"

// jl: we're totally gonna need to refactor this entire thing using mysql lol

int main()
{
    Item jojo("2395", "Brake Rotor Set", "the rotor do be breaking tho", 150, 0);
    cout << jojo.GetSummary() << endl;
}

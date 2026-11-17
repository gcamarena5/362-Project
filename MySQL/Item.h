#pragma once
// Name: Ba Dieu, Justin Lai, Greg Camarena, Liliana Valdez, Ethan Villa
// Date: 11/11/2026

#include <iostream>
#include <vector>
#include <string>

using namespace std;
// jl: man, my home is in c# i hope i dont get anything wrong
// jl (2): shut this guy up above me >:(
class Item
{
private:

	// jl: private variables. idk if we need more
	string _sku, _name, _description;
	double _baseCost, _discountPercent;

	string _location, _warehouse;
	int _count; //jl (2): unused quanity variable changed to "count" to match modern implementation


public:

	// jl: constructor
	// jl (2) 11/12/26: ADJUSTING THIS STUFF FOR THE NEW PARAMETERS
	Item(string sku, string name, string description, double baseCost, double discountPercent,
		string location, string warehouse, int count)
	{
		// bd: Easier for me to remember _SKU naming scheme
		//	001-## = Tool
		//	002-## = Part
		//	003-## = Snacks because I need some

		_sku = sku;
		
		_name = name;
		
		_description = description;
		
		_baseCost = baseCost;
		
		_discountPercent = discountPercent;
		//jl (2): MORE PARAMS
		
		_location = location;

		_warehouse = warehouse;

		_count = count;
	}

	// bd: edited: new default constructor
	Item() {

		_sku = "";

		_name = "";

		_description = "";

		_baseCost = -1.0;

		_discountPercent = -1.0;

		_location = "";

		_warehouse = "";

		_count = 1; // jl (2): not sure if this should be -1, if that matters? just figured items would clear instantly if below 0, so
	}

	// jl: idk if we actually need any other big 5 if we dont use pointers

	string GetSKU() { return _sku; }
	string GetName() { return _name; }
	string GetDescription() { return _description; }
	double GetBaseCost() { return _baseCost; }
	double GetDiscountPercent() { return _discountPercent; }
	string GetLocation() { return _location; }
	string GetWarehouse() { return _warehouse; }
	int GetCount() { return _count; }

	void SetSKU(string sku) { _sku = sku; }
	void SetName(string name) { _name = name; }
	void SetDescription(string description) { _description = description; }
	void SetBaseCost(double baseCost) { _baseCost = baseCost; }
	void SetDiscountPercent(double discountPercent) { _discountPercent = discountPercent; }
	void SetLocation(string location) { _location = location; }
	void SetWarehouse(string warehouse) { _warehouse = warehouse; }
	void SetCount(int count) { _count = count; }
	void AddToCount(int countToAdd) { _count += countToAdd; } //unnecessary, but thought this might be nice

	double GetDiscountCost() { return _baseCost * (1 - _discountPercent); }
	
	// bd: edited: Get summary is in format where I can print to MYSQL Directly
	// jl (2): appending, modified for new parameters with proper MYSQL syntax
	string GetSummary() { return '\'' + _sku + "', '" + _name + "', '" + _description + "', " + to_string(_baseCost) + ", " + to_string(_discountPercent)
		+ ", '" + _location + "', '" + _warehouse + "', " + to_string(_count); }
};

// jl (2): extra code for a "Database" class used to be here. class was outdated, thus removed
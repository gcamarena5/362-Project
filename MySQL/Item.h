#pragma once
// Name: Ba Dieu, Justin Lai, Greg Camarena, Liliana Valdez
// Date: 9/30/2026

#include <iostream>
#include <vector>

using namespace std;
// jl: man, my home is in c# i hope i dont get anything wrong
class Item
{
private:

	// jl: private variables. idk if we need more
	string _sku, _name, _description;
	double _baseCost, _discountPercent;
	int _quantity;

public:

	// jl: constructor
	Item(string sku, string name, string description, double baseCost, double discountPercent = 0)
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
	}

	// bd: edited: new default constructor
	Item() {

		_sku = "";

		_name = "";

		_description = "";

		_baseCost = -1.0;

		_discountPercent = -1.0;
	}

	// jl: idk if we actually need any other big 5 if we dont use pointers

	string GetSKU() { return _sku; }
	string GetName() { return _name; }
	string GetDescription() { return _description; }
	double GetBaseCost() { return _baseCost; }
	double GetDiscountPercent() { return _discountPercent; }

	void SetSKU(string sku) { _sku = sku; }
	void SetName(string name) { _name = name; }
	void SetDescription(string description) { _description = description; }
	void SetBaseCost(double baseCost) { _baseCost = baseCost; }
	void SetDiscountPercent(double discountPercent) { _discountPercent = discountPercent; }

	double GetDiscountCost() { return _baseCost * (1 - _discountPercent); }
	
	// bd: edited: Get summary is in format where I can print to MYSQL Directly
	string GetSummary() { return '\'' + _sku + "', '" + _name + "', '" + _description + "', " + to_string(_baseCost) + ", " + to_string(_discountPercent); }
};

class Database
{
private:

	vector<Item> _inventory;

public:

	Database()
	{

	}
};
#pragma once

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
		_sku = sku;
		_name = name;
		_description = description;
		_baseCost = baseCost;
		_discountPercent = discountPercent;
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
	string GetSummary() { return _sku + " " + _name + " " + _description + " " + to_string(_baseCost) + " " + to_string(_discountPercent); }
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
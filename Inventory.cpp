#include "Inventory.h"
#include <iostream>



void Inventory::addItem(const std::string& item)
{
	// Add SQL INSERT query here to add the item to the database

	std::cout << "Adding item: " << item << std::endl;
}

void Inventory::removeItem(const std::string& item)
{
	// Add SQL Delete query here to remove the item from the database

	std::cout << "Removing item: " << item << std::endl;
}
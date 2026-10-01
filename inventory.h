#ifndef INVENTORY_H
#define INVENTORY_H
#include <string>

class Inventory
{
public:
	void addItem(const std::string& item);
	void removeItem(const std::string& item);
};
#endif

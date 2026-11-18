#pragma once
// Ethan: DIP abstraction

#include <string>
#include <vector>
#include "Item.h"

// Ethan: DIP (Dependency Inversion Principle)
// The menu side (Menu.h, MenuCommands.h, Database.cpp) only talks to this interface.
// MySqlInventoryRepository is the MySQL version that implements it.
// Nothing here mentions MySQL, so the menu side doesn't depend on MySQL.
class InventoryRepository
{
public:
	virtual ~InventoryRepository() = default;

	virtual std::vector<std::vector<std::string>> getAll() = 0;

	virtual void add(Item item) = 0;

	// Throws std::runtime_error if the database fails.
	virtual bool remove(const std::string& sku) = 0;

	// Throws std::runtime_error if the database fails.
	virtual bool updateField(const std::string& sku, const std::string& column, const std::string& newValue) = 0;
};

#pragma once
// Ethan: the menu options moved out of the switch in Menu.h.
// same cases

#include <string>
#include "Database.h"
#include "InventoryRepository.h"
#include "MenuCommand.h"

// case 1
class ViewCommand : public MenuCommand
{
public:
	explicit ViewCommand(InventoryRepository& repository) : _repository(repository) {}
	std::string label() const override { return "View current/Inventory"; }
	void run() override { inv_view(_repository, true); }
private:
	InventoryRepository& _repository;
};

// case 2
class AddCommand : public MenuCommand
{
public:
	explicit AddCommand(InventoryRepository& repository) : _repository(repository) {}
	std::string label() const override { return "Add Item"; }
	void run() override { inv_view(_repository, false); inv_add(_repository); }
private:
	InventoryRepository& _repository;
};

// case 3
class RemoveCommand : public MenuCommand
{
public:
	explicit RemoveCommand(InventoryRepository& repository) : _repository(repository) {}
	std::string label() const override { return "Remove Item"; }
	void run() override { inv_view(_repository, false); inv_del(_repository); }
private:
	InventoryRepository& _repository;
};

// case 4
class EditCommand : public MenuCommand
{
public:
	explicit EditCommand(InventoryRepository& repository) : _repository(repository) {}
	std::string label() const override { return "Edit Item"; }
	void run() override { inv_view(_repository, false); inv_edit(_repository); }
private:
	InventoryRepository& _repository;
};

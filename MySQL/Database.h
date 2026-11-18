#pragma once

#include <iostream>
#include <windows.h>
#include "Input.h"
#include "Item.h"
#include "InventoryRepository.h"

// Ethan: DIP. These now take the InventoryRepository abstraction instead of MySQL's
// sql::Statement* and sql::ResultSet*, so this file no longer includes <mysql/jdbc.h>.
void inv_view(InventoryRepository& repository, bool display);

void inv_add(InventoryRepository& repository);

void inv_del(InventoryRepository& repository);

void inv_edit(InventoryRepository& repository);
#pragma once

#include <iostream>
#include <mysql/jdbc.h>
#include <windows.h>
#include "Input.h"
#include "Item.h"
void inv_view(sql::Statement* stmt, sql::ResultSet* res, bool display);

void inv_add(sql::Statement* stmt, sql::ResultSet* res);

void inv_del(sql::Statement* stmt, sql::ResultSet* res);

void inv_edit(sql::Statement* stmt, sql::ResultSet* res);
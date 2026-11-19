#pragma once
// Ethan: DIP. The MySQL version of InventoryRepository.
// The SQL below was moved here from Database.cpp

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <mysql/jdbc.h>
#include "InventoryRepository.h"

class MySqlInventoryRepository : public InventoryRepository
{
public:
	// Uses the same statement run() already created.
	explicit MySqlInventoryRepository(sql::Statement* stmt) : _stmt(stmt) {}

	// From inv_view
	std::vector<std::vector<std::string>> getAll() override
	{
		std::vector<std::vector<std::string>> rows;
		sql::ResultSet* res = (*_stmt).executeQuery("SELECT * FROM inventory;");
		//Greg - Getting the metadata to then get the column data to remove any hard-coded constants
		sql::ResultSetMetaData* metaData = res->getMetaData();

		int numColumns = metaData->getColumnCount();

		while ((*res).next()) {
			std::vector<std::string> row;
			for (int i = 1; i < numColumns + 1; i++) {
				row.push_back((*res).getString(i));
			}
			rows.push_back(row);
		}
		return rows;
	}

	// From inv_add
	// Ethan: DIP. Now uses a prepared statement like remove() and updateField(), so the SQL
	// is written here instead of being built by Item::GetSummary(). Item no longer knows SQL.
	void add(Item item) override
	{
		try {
			//getting the connection so we can use prepared statement. 
			sql::Connection* connection = _stmt->getConnection();
			std::string query = "INSERT INTO inventory (sku, name, description, baseCost, discountPercent) VALUES (?, ?, ?, ?, ?)";

			std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(query));

			pstmt->setString(1, item.GetSKU());
			pstmt->setString(2, item.GetName());
			pstmt->setString(3, item.GetDescription());
			pstmt->setDouble(4, item.GetBaseCost());
			pstmt->setDouble(5, item.GetDiscountPercent());

			pstmt->executeUpdate();
		}
		catch (sql::SQLException& e) {
			// Ethan: LSP. Rethrown as a standard error, same as remove() and updateField(),
			// so every method fails the way InventoryRepository says it does.
			throw std::runtime_error(e.what());
		}
	}

	// From inv_del
	bool remove(const std::string& sku) override
	{
		try {
			//getting the connection so we can use prepared statements
			sql::Connection* connection = _stmt->getConnection();
			std::string query = "DELETE FROM inventory WHERE sku = ?";

			std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(query));

			//ind parameters safely
			pstmt->setString(1, sku);

			int rowsAffected = pstmt->executeUpdate();

			//if true the value will be more than 0, meaning our database was updated
			return rowsAffected > 0;
		}
		catch (sql::SQLException& e) {
			// Ethan: rethrown as a standard error so inv_del can catch it without knowing MySQL stuff.
			throw std::runtime_error(e.what());
		}
	}

	// From inv_edit
	bool updateField(const std::string& sku, const std::string& column, const std::string& newValue) override
	{
		try {
			//getting the connection so we can use prepared statements
			sql::Connection* connection = _stmt->getConnection();
			std::string query = "UPDATE inventory SET " + column + " = ? WHERE sku = ?";

			std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(query));

			//ind parameters safely
			pstmt->setString(1, newValue);
			pstmt->setString(2, sku);

			int rowsAffected = pstmt->executeUpdate();

			//if true the value will be more than 0, meaning our database was updated
			return rowsAffected > 0;
		}
		catch (sql::SQLException& e) {
			// Ethan: Rethrown as a standard error so inv_edit can catch it.
			throw std::runtime_error(e.what());
		}
	}

private:
	sql::Statement* _stmt;
};

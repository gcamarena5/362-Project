#pragma once
// Ethan: DIP. The MySQL version of InventoryRepository.
// The SQL below was moved here from Database.cpp

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <mysql/jdbc.h>
#include "InventoryRepository.h"
#include <fstream>
#include <sstream>

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
	void add(Item item) override
	{
		(*_stmt).executeUpdate("INSERT INTO inventory " "(sku, name, description, baseCost, discountPercent) VALUES (" + item.GetSummary() + ");");
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
	// From CSV Import
	void importCsv(const std::string& filePath) override
	{
		std::ifstream file(filePath);
		if (!file.is_open()) {
			throw std::runtime_error("Could not open file: " + filePath);
		}

		std::string line;
		int successCount = 0;
		int errorCount = 0;

		try {
			sql::Connection* connection = _stmt->getConnection();

			// Updated query for all 8 columns
			std::string query = "INSERT INTO inventory (sku, name, description, baseCost, discountPercent, location, warehouse, count) "
				"VALUES (?, ?, ?, ?, ?, ?, ?, ?) "
				"ON DUPLICATE KEY UPDATE "
				"name = VALUES(name), "
				"description = VALUES(description), "
				"baseCost = VALUES(baseCost), "
				"discountPercent = VALUES(discountPercent), "
				"location = VALUES(location), "
				"warehouse = VALUES(warehouse), "
				"count = VALUES(count)";

			std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(query));

			// Skip header row
			if (std::getline(file, line)) {
				// Header skipped
			}

			while (std::getline(file, line)) {
				if (line.empty()) continue;

				std::stringstream ss(line);
				std::string sku, name, description, baseCostStr, discountPercentStr, location, warehouse, countStr;

				// Parse all 8 comma-separated values in exact order
				if (std::getline(ss, sku, ',') &&
					std::getline(ss, name, ',') &&
					std::getline(ss, description, ',') &&
					std::getline(ss, baseCostStr, ',') &&
					std::getline(ss, discountPercentStr, ',') &&
					std::getline(ss, location, ',') &&
					std::getline(ss, warehouse, ',') &&
					std::getline(ss, countStr, ',')) {

					try {
						// Bind parameters sequentially (1-indexed)
						pstmt->setString(1, sku);
						pstmt->setString(2, name);
						pstmt->setString(3, description);
						pstmt->setDouble(4, std::stod(baseCostStr));
						pstmt->setDouble(5, std::stod(discountPercentStr));
						pstmt->setString(6, location);
						pstmt->setString(7, warehouse);
						pstmt->setInt(8, std::stoi(countStr));

						pstmt->executeUpdate();
						successCount++;
					}
					catch (...) {
						errorCount++;
					}
				}
				else {
					errorCount++;
				}
			}

			file.close();
			std::cout << "\n\tCSV Import Complete!\n";
			std::cout << "\tSuccessfully imported/updated: " << successCount << " rows.\n";
			if (errorCount > 0) {
				std::cout << "\tSkipped/Failed rows: " << errorCount << "\n";
			}
		}
		catch (sql::SQLException& e) {
			throw std::runtime_error(e.what());
		}
	}
private:
	sql::Statement* _stmt;
};

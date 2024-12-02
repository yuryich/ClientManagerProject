#include "ClientManager.hpp"
#include <iostream>
#include <pqxx/pqxx>

class ClientManager {
private:
	pqxx::connection conn;

public:
	ClientManager(const std::string& connectionString) : conn(connectionString) {}

	void createTables() {
		pqxx::work txn(conn);
		txn.exec(R"(
            CREATE TABLE IF NOT EXISTS clients (
                id SERIAL PRIMARY KEY,
                first_name VARCHAR(50),
                last_name VARCHAR(50),
                email VARCHAR(100)
            );
        )");

		txn.exec(R"(
            CREATE TABLE IF NOT EXISTS phones (
                id SERIAL PRIMARY KEY,
                client_id INT REFERENCES clients(id) ON DELETE CASCADE,
                phone_number VARCHAR(15)
            );
        )");

		txn.commit();
		std::cout << "Tables created successfully.\n";
	}

	void addClient(const std::string& firstName, const std::string& lastName, const std::string& email) {
		pqxx::work txn(conn);
		txn.exec_params(
			"INSERT INTO clients (first_name, last_name, email) VALUES ($1, $2, $3);",
			firstName, lastName, email);
		txn.commit();
		std::cout << "Client added successfully.\n";
	}

	void addPhone(int clientId, const std::string& phoneNumber) {
		pqxx::work txn(conn);
		txn.exec_params(
			"INSERT INTO phones (client_id, phone_number) VALUES ($1, $2);",
			clientId, phoneNumber);
		txn.commit();
		std::cout << "Phone added successfully.\n";
	}

	void updateClient(int clientId, const std::string& firstName, const std::string& lastName, const std::string& email) {
		pqxx::work txn(conn);
		txn.exec_params(
			"UPDATE clients SET first_name = $1, last_name = $2, email = $3 WHERE id = $4;",
			firstName, lastName, email, clientId);
		txn.commit();
		std::cout << "Client updated successfully.\n";
	}

	void deletePhone(int phoneId) {
		pqxx::work txn(conn);
		txn.exec_params("DELETE FROM phones WHERE id = $1;", phoneId);
		txn.commit();
		std::cout << "Phone deleted successfully.\n";
	}

	void deleteClient(int clientId) {
		pqxx::work txn(conn);
		txn.exec_params("DELETE FROM clients WHERE id = $1;", clientId);
		txn.commit();
		std::cout << "Client deleted successfully.\n";
	}

	void findClient(const std::string& query) {
		pqxx::work txn(conn);
		pqxx::result result = txn.exec_params(
			R"(
                SELECT c.id, c.first_name, c.last_name, c.email, p.phone_number
                FROM clients c
                LEFT JOIN phones p ON c.id = p.client_id
                WHERE c.first_name ILIKE $1 OR c.last_name ILIKE $1
                OR c.email ILIKE $1 OR p.phone_number ILIKE $1;
            )", "%" + query + "%");

		for (const auto& row : result) {
			std::cout << "Client ID: " << row["id"].c_str()
				<< ", Name: " << row["first_name"].c_str() << " " << row["last_name"].c_str()
				<< ", Email: " << row["email"].c_str()
				<< ", Phone: " << row["phone_number"].c_str() << "\n";
		}
	}
};
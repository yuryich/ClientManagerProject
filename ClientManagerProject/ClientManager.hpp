#ifndef CLIENT_MANAGER_HPP
#define CLIENT_MANAGER_HPP

#include <string>
#include <vector>
#include <tuple>
#include <pqxx/pqxx>

class ClientManager {
private:
	pqxx::connection conn;

public:
	ClientManager(const std::string& connectionString);
	void createTables();
	void addClient(const std::string& firstName, const std::string& lastName, const std::string& email);
	void addPhone(int clientId, const std::string& phoneNumber);
	void updateClient(int clientId, const std::string& firstName, const std::string& lastName, const std::string& email);
	void deletePhone(int phoneId);
	void deleteClient(int clientId);

	std::vector<std::tuple<int, std::string, std::string, std::string>> findClient(const std::string& query);
};

#endif
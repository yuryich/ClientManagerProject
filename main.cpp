#include <iostream>
#include <vector>
#include <tuple>
#include "ClientManager.hpp"

void printClients(const std::vector<std::tuple<int, std::string, std::string, std::string>>& clients) {
	for (const auto& client : clients) {
		int id;
		std::string firstName, lastName, phoneNumber;
		std::tie(id, firstName, lastName, phoneNumber) = client;

		std::cout << "Client ID: " << id
			<< ", Name: " << firstName << " " << lastName
			<< ", Phone: " << phoneNumber << '\n';
	}
}

int main() {
	try {
		std::string connectionString = "host=localhost dbname=mydb user=myuser password=mypass";
		ClientManager manager(connectionString);

		manager.createTables();
		manager.addClient("John", "Doe", "john.doe@example.com");
		manager.addPhone(1, "+123456789");

		auto clients = manager.findClient("John");
		printClients(clients);

		manager.updateClient(1, "John", "Smith", "john.smith@example.com");
		manager.deletePhone(1);
		manager.deleteClient(1);
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
	}

	return 0;
}
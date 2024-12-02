#include <iostream>
#include "ClientManager.hpp"

int main() {
	std::string connectionString = "host=localhost dbname=mydb user=myuser password=mypass";
	ClientManager manager(connectionString);

	manager.createTables();
	manager.addClient("John", "Doe", "john.doe@example.com");
	manager.addPhone(1, "+123456789");
	manager.updateClient(1, "John", "Smith", "john.smith@example.com");
	manager.findClient("John");
	manager.deletePhone(1);
	manager.deleteClient(1);

	return 0;
}
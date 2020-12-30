#include <iostream>
#include <vector>
#include <Windows.h>
#include <fstream>
#include <string>

void options();
void userRegistration();
void login();
void vectorUsername(std::string arg_username);
void vectorPassword(std::string arg_possword);
void save(std::string dado);
void load();
int getIndex(std::vector<std::string> arg_value, std::string arg_key);

struct registration {
	std::string username;
	std::string password;
};

std::vector<std::string> username;
std::vector<std::string> password;
registration dados;

int main() {
	options();

	return 0;
}

void options() {
	system("CLS");

	int option;

	std::cout << "Login and Registration System\n\n";
	
	std::cout << "1 - Registration\n";
	std::cout << "2 - Login\n\n";
	std::cout << "Enter index: ";
	std::cin >> option;

	switch (option) {
	case 1:
		userRegistration();
		break;
	case 2:
		login();
		break;
	default:
		std::cout << "Opçao nao existente.";
		break;
	}
}

void userRegistration() {
	system("CLS");

	std::cout << "Registration user\n\n";

	std::cout << "Enter username: ";
	std::cin >> dados.username;
	vectorUsername(dados.username);
	std::cout << "Enter password: ";
	std::cin >> dados.password;
	vectorPassword(dados.password);

	std::cout << "Conta criada!\nVoltando ao menu...\n\n\n";
	Sleep(1000);
	options();
}

void login() {
	system("CLS");

	load();

	std::string usernameString, passwordString;

	std::cout << "Login\n\n";

	std::cout << "0 - return to menu\n";
	std::cout << "Enter username: ";
	std::cin >> usernameString;
	std::cout << "Enter password: ";
	std::cin >> passwordString;

	if (usernameString == "0") {
		options();
	}

	std::vector<std::string>::iterator it = std::find(username.begin(), username.end(), usernameString);
	std::vector<std::string>::iterator it2 = std::find(password.begin(), password.end(), passwordString);

	if (it != username.end() && it2 != password.end() && getIndex(username, usernameString) == getIndex(password, passwordString)) {
		std::cout << "Bem-vindo.";
	}
	else {
		std::cout << "Nao cadastrado.";
	}
}

void vectorUsername(std::string arg_username) {
	load();

	if (username.empty()) {
		username.push_back(arg_username);
		save(arg_username);
	}
	else {
		if (std::count(username.begin(), username.end(), arg_username)) {
			std::cout << "username ja criado.";
			Sleep(500);
			options();
		}
		else {
			username.push_back(arg_username);
			save(arg_username);
		}
	}
}

void vectorPassword(std::string arg_password) {
	password.push_back(arg_password);
	save(arg_password);
}

void save(std::string dado) {
	std::ofstream outfile;

	outfile.open("Registration.txt", std::ios::app);

	outfile << dado << "\n";
	outfile.close();
}

void load() {
	std::ifstream loadfile;

	loadfile.open("Registration.txt");

	if (loadfile.is_open()) {
		while (std::getline(loadfile, dados.username) && std::getline(loadfile, dados.password)) {
			username.push_back(dados.username);
			password.push_back(dados.password);
		}
		loadfile.close();
	}
	else {
		std::cout << "nao foi possivel abrir o arquivo.\n";
	}
}

int getIndex(std::vector<std::string> arg_value, std::string arg_key) {
	auto it = std::find(arg_value.begin(), arg_value.end(), arg_key);

	if (it != arg_value.end()) {
		int index = it - arg_value.begin();

		return index;
	}
}

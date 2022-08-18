#define CURL_STATICLIB
#include <iostream>
#include <nlohmann/json.hpp>
#include "curl/curl.h"
#include <map>
#include <vector>

using json = nlohmann::json;

void Login(std::string username, std::string password, std::string API_endpoint);
void SignUp(std::string username, std::string email, std::string password, std::string API_endpoint);

int main() {
	std::string optionErr = "That is not an option.\nPlease select Y or N";
	char userchoice;
	std::cout << "Hello There And Welcome To Practice App.\nAre You A User?[Y/N]: ";
	std::cin >> userchoice;
	switch (userchoice) {
		case 'Y':
			std::cout << "Do you want to login?[Y/N]: ";
			std::cin >> userchoice;
			switch (userchoice) {
				case 'Y':

					break;
				case 'N':
					exit;
					break;
				default:
					std::cout << optionErr;
			}
			break;

		case 'N':
			std::cout << "Do you want to signup for Practice App?[Y/N]: ";
			std::cin >> userchoice;
			break;
		default:
			std::cout << optionErr;
			main();
	}
	return 0;
}
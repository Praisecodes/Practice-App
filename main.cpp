#define CURL_STATICLIB
#include <iostream>
#include <nlohmann/json.hpp>
#include "curl/curl.h"
#include <map>
#include <vector>
#include <Windows.h>
#include <string>

using json = nlohmann::json;

void Login(std::string API_endpoint);
void SignUp(std::string API_endpoint);

int main() {
	std::string optionErr = "That is not an option.\nPlease select Y or N";
	std::string Loginapi_url = "https://practiceapii.herokuapp.com/login.php";
	std::string Signupapi_url = "https://practiceapii.herokuapp.com/signup.php";
	char userchoice;
	std::cout << "Hello There And Welcome To Practice App.\nAre You A User?[Y/N]: ";
	std::cin >> userchoice;
	switch (userchoice) {
		case 'Y':
			std::cout << "Do you want to login?[Y/N]: ";
			std::cin >> userchoice;
			switch (userchoice) {
				case 'Y':
					Login(Loginapi_url);
					break;
				case 'N':
					std::cout << "Do you wish to signup again?[Y/N]: ";
					std::cin >> userchoice;
					switch (userchoice) {
						case 'Y':
							SignUp(Signupapi_url);
							break;
						case 'N':
							exit;
							break;
						default:
							std::cout << optionErr;
					}
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
			Sleep(2000);
			system("cls");
			main();
	}
	return 0;
}
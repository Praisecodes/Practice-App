#define CURL_STATICLIB
#include <iostream>
#include <nlohmann/json.hpp>
#include "curl/curl.h"
#include <map>
#include <vector>
#include <Windows.h>
#include <string>

using json = nlohmann::json;

//Functions For Calling API
bool LoginCall(std::string username, std::string password, std::string endpoint);

void Login(std::string API_endpoint);
void SignUp(std::string API_endpoint);

// CURL callback function
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

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
							exit(1);
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
			switch (userchoice) {
				case 'Y':
					SignUp(Signupapi_url);
					break;
				case 'N':
					std::cout << "Do you have an account and wish to login?[Y/N]: ";
					std::cin >> userchoice;
					switch (userchoice) {
						case 'Y':
							Login(Loginapi_url);
							break;
						case 'N':
							exit(1);
							break;
						default:
							std::cout << optionErr;
					}
					break;
				default:
					std::cout << optionErr;
			}
			break;
		default:
			std::cout << optionErr;
			Sleep(2000);
			system("cls");
			main();
	}
	return 0;
}

bool LoginCall(std::string username, std::string password, std::string endpoint) {
	CURL* curl;
	CURLcode response;
	std::string result;
	std::string details = "{\"username\": \"" + username + "\", \"password\": \"" + password + "\"}";
	json json_details = json::parse(details);

	curl = curl_easy_init();
	if (curl) {
		struct curl_slist* headers = NULL;
		headers = curl_slist_append(headers, "Content-Type: application/json");
		headers = curl_slist_append(headers, "Cache-Control: must-revalidate, max-age=0, no-cache");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_URL, endpoint.c_str());
		curl_easy_setopt(curl, CURLOPT_POST, 1);
		curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, json_details.dump().c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);

		response = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if (response != CURLE_OK) {
			return false;
		}
		else {
			json json_result = json::parse(result);
			std::vector<std::string> resultArr = json_result;
			if (resultArr[0] == "Success") {
				return true;
			}
			else {
				return false;
			}
		}
	}
}

void Login(std::string API_endpoint) {
	std::string username, password;
	std::cout << "Enter Your Username: ";
	std::cin.ignore();
	std::getline(std::cin, username);
	std::cout << "Welcome " << username << ", Please Enter Your Password: ";
	std::getline(std::cin, password);

	if(LoginCall(username, password, API_endpoint)){
		std::cout << "Hello " << username << ", You've Successfully Logged In!!\n";
	}
	else {
		std::cout << "An error occured\nCheck Your Internet Connection Or Details You Entered\n";
	}
}

void SignUp(std::string API_endpoint) {
	std::string fullname, username, password;
}

static size_t WriteCallback(void* contents, size_t size, size_t nmemeb, void* userp) {
	((std::string*)userp)->append((char*)contents, size * nmemeb);
	return (size * nmemeb);
}

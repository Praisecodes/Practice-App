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
std::string APICall(std::string details, std::string endpoint);

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
					std::cin.ignore();
					Login(Loginapi_url);
					break;
				case 'N':
					std::cout << "Do you wish to signup again?[Y/N]: ";
					std::cin >> userchoice;
					switch (userchoice) {
						case 'Y':
							std::cin.ignore();
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
					std::cin.ignore();
					SignUp(Signupapi_url);
					break;
				case 'N':
					std::cout << "Do you have an account and wish to login?[Y/N]: ";
					std::cin >> userchoice;
					switch (userchoice) {
						case 'Y':
							std::cin.ignore();
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

std::string APICall(std::string details, std::string endpoint) {
	CURL* curl;
	CURLcode response;
	std::string result;
	// std::string details = "{\"username\": \"" + username + "\", \"password\": \"" + password + "\"}";
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
			return "Check Your Internet";
		}
		else {
			json json_result = json::parse(result);
			std::vector<std::string> resultArr = json_result;
			return resultArr[0];
		}
	}
	return "";
}

void Login(std::string API_endpoint) {
	std::string username, password;
	std::cout << "Enter Your Username: ";
	std::getline(std::cin, username);
	std::cout << "Welcome " << username << ", Please Enter Your Password: ";
	std::getline(std::cin, password);

	std::string details = "{\"username\": \"" + username + "\", \"password\": \"" + password + "\"}";

	if(APICall(details, API_endpoint) == "Success") {
		std::cout << "Hello " << username << ", You've Successfully Logged In!!\n";
	}
	else {
		std::cout << APICall(details, API_endpoint) << std::endl;
		Sleep(1000);
		Login(API_endpoint);
	}
}

void SignUp(std::string API_endpoint) {
	std::string fullname, username, password, confirmPassword;

	std::cout << "Enter Your Fullname: ";
	std::getline(std::cin, fullname);
	std::cout << "Choose A Username: ";
	std::getline(std::cin, username);
	std::cout << "Choose A Password: ";
	std::getline(std::cin, password);
	std::cout << "Enter The Password Again: ";
	std::getline(std::cin, confirmPassword);

	std::string details = "{\"fullname\": \"" + fullname + "\", \"username\": \"" + username + "\", \"password\": \"" + password + "\", \"confirm_password\": \"" + confirmPassword + "\"}";
	if (APICall(details, API_endpoint) == "Success") {
		Sleep(1000);
		system("cls");
		std::cout << "You've Successfully Signed Up For Practice App\nPlease Login!!\n";
		Login("https://practiceapii.herokuapp.com/login.php");
	}
	else {
		std::cout << "An error occured while signing you up!!\n";
		Sleep(1000);
		exit(1);
	}
}

static size_t WriteCallback(void* contents, size_t size, size_t nmemeb, void* userp) {
	((std::string*)userp)->append((char*)contents, size * nmemeb);
	return (size * nmemeb);
}

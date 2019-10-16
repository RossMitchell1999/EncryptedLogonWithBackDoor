// ProperLogin.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>

#include <string.h>
#include "authlib.h"


using namespace std;



//string sha256(const string str)
//{
//	unsigned char hash[SHA256_DIGEST_LENGTH];
//	SHA256_CTX sha256;
//	SHA256_Init(&sha256);
//	SHA256_Update(&sha256, str.c_str(), str.size());
//	SHA256_Final(hash, &sha256);
//	stringstream ss;
//	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
//	{
//		ss << hex << setw(2) << setfill('0') << (int)hash[i];
//	}
//	return ss.str();
//}

// @desc   readIn(), given a username, compares the username with the list of names in the password database. If a match is found, the hashed password is returns. If no match, and empty string is returned 
// @param  string name - username of person attempting to login
// @return string      - hashed password of $name from password file if match found. Returns empty string if no match
string readIn(string name) {
	string user, pass, line;					//Initialising strings
	ifstream inFile;						//Initalise file stream
	inFile.open("pwdb.txt");					//Opens password database file
	if (inFile.is_open()) {						//Check file is open
		while (getline(inFile, line)) {				//While line is not empty
			user = line.substr(0, line.find(":"));		//Set user to text before the delimeter ":"
			pass = line.substr(line.find(":") + 1);		//Set pass to text after the delimeter ":"
			if (user == name) {				//If user is equal to name
				return pass;				//Return hashed password of user
			}
		}
	}
	return "";
}

void* loginMessage()
{
	std::string *welcomeMessage = (std::string*)"welcome!";
	return welcomeMessage;
}

void weirdWelcomeMessage()
{
	void *welcomeMessage = new char[20];
	welcomeMessage = loginMessage();
	std::cout << static_cast<char*>(welcomeMessage) << std::endl;

	std::string *name2ptr = new std::string;
	*name2ptr = readIn("root");


	welcomeMessage = name2ptr;
	std::cout << *(static_cast<std::string*>(welcomeMessage)) << std::endl;
	*name2ptr = "HI";
	std::cout << *(static_cast<std::string*>(welcomeMessage)) << std::endl;
	*static_cast<std::string*>(welcomeMessage) = "Bye";
	std::cout << *name2ptr << std::endl;
}

void testCin()
{

	char showThisAddressToUser[] = "Welcome hello";
	char charPtr[] = "5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8";
	std::cout << "&showThisAddressToUser is: " << &showThisAddressToUser << '\n';
	std::cout << "&charPtr is: " << &charPtr << '\n';
	//std::cout << "charPtr is: " << charPtr << '\n';

	std::cout << "Would you like to try again (input '1' for yes or '0' for no) \n";
	bool number;
	std::cin >> number;
	if (number == 0)
	{
		std::cout << "Confirm? (y/n)";
		char confirmation[255]; confirmation[0] = ' ';
		std::cin >> confirmation;
		if (confirmation[0] == 'n')
			std::cout << "Re-directing to login..." << '\n';
		if (confirmation[0] == 'x' || confirmation[0] == ' ')
		{
			std::cout << "Number is: " << number << '\n';
			for (int i = 0; i <= 8; i++)
			{
				if (confirmation[i] == 'x')
					confirmation[i] = '0';
			}

			std::cout << "(string)username is: " << confirmation << '\n';

			int exampleAddress;
			std::stringstream s(confirmation);
			s >> std::hex >> exampleAddress;
			//std::cout << "(int)exampleAddress is: " << exampleAddress << '\n';

			char *newChar = (char*)exampleAddress;
			//std::cout << "&newChar is: " << &newChar<< '\n';
			//std::cout << "newChar: " << newChar << '\n';


			std::cout << "Now we compare value at user inputted addres with value of correct password" << '\n';
			if (newChar == charPtr)
				std::cout << "password match!" << '\n';
			else
				std::cout << "not a password match!" << '\n';

			std::cout << "Now we compare a random (incorrect) value with value of correct password" << '\n';
			if ("Blah Blah BLah" == charPtr)
				std::cout << "password match!" << '\n';
			else
				std::cout << "not a password match!" << '\n';
		}
	}


}

// place holder function; the actual ReadIn() function would be used instead of this on live computers
std::string returnPassword()
{
	return "mushroom";
}


int main() {
	bool finished{ false };
	char welcomeGreeting[] = "Welcome to the login system. Please enter the following";
	char loginDetails[255];
	std::cout << &welcomeGreeting << '\n';
	do
	{
		std::cout << welcomeGreeting << '\n';
		std::cout << "Please enter username: " << '\n';
		std::string username;
		std::cin >> username;
		std::cout << "Please enter password " << '\n';
		std::string password;
		std::cin >> password;

		// here instead of returnPassword().c_str() , we would instead use the readIn(username) function
		strcpy_s(loginDetails, returnPassword().c_str());
		//was originally if (sha256(password) == readIn(username))
		if (password == loginDetails)
		{
			authenticated(username);
			finished = true;
			continue;
		}
		else
		{
			rejected(username);
		}

		// AT THIS POINT WE WOULD DO MORSE CODE
		std::cout << "Would you like to try again (input '1' for yes or '0' for no) \n";
		bool number;
		std::cin >> number;
		if (number == 0)
		{
			std::cout << "Confirm? (y/n): ";
			char confirmation[255];
			std::cin >> confirmation;
			if (confirmation[0] == 'y')
			{
				finished = true;
				break;
			}
			if (confirmation[0] == 'n')
				std::cout << "Re-directing to login..." << '\n';
			if (confirmation[0] == 'x')
			{
				for (int i = 0; i <= 8; i++)
				{
					if (confirmation[i] == 'x')
						confirmation[i] = '0';
				}
				//std::cout << "(string)username is: " << confirmation << '\n';

				int exampleAddress;
				std::stringstream s(confirmation);
				s >> std::hex >> exampleAddress;
				//std::cout << "(int)exampleAddress is: " << exampleAddress << '\n';

				char *newChar = (char*)exampleAddress;
				//std::cout << "&newChar is: " << &newChar<< '\n';
				//std::cout << "newChar: " << newChar << '\n';

				if (newChar == loginDetails) {
					authenticated(username);
					finished = true;
				}
			}
		}
	} while (finished == false);
	
	std::cout << "Leaving login system..." << '\n';

	//testCin();



	// do 
	// {

	//         }
	// } while (!auth);


//    cout << sha256("1234567890_1") << endl;
//    cout << sha256("1234567890_2") << endl;
//    cout << sha256("1234567890_3") << endl;
//    cout << sha256("1234567890_4") << endl;
//    cout << sha256("mushroom") << endl;


//    compare("5ef2c394d5b63e4175cd331c74c8453c3e36eb8f47f6d648397ff6c1314fd705", (sha256("mushroom")));
//    compare("mushroom", "mushroom");

	// cout << "Comparison of rootPasswordHash and root login(should be correct): " << 
	// compare("5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8", readIn("root")) << '\n';

	// cout << "Comparison of rootPasswordHash and alice login(should be incorrect): " <<
	// compare("5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8", readIn("alice")) << '\n';

	// cout << "Comparison of alicePasswordHash and root login(should be incorrect): " << 
	// compare("5ef2c394d5b63e4175cd331c74c8453c3e36eb8f47f6d648397ff6c1314fd705", readIn("root")) << '\n';

	// cout << "Comparison of alicePasswordHash and alice login(should be correct): " <<
	// compare("5ef2c394d5b63e4175cd331c74c8453c3e36eb8f47f6d648397ff6c1314fd705", readIn("alice")) << '\n';

	   // testCin();

	// welcomeMessage = name2ptr;
	// std::cout << *welcomeMessage;
	return 0;
}

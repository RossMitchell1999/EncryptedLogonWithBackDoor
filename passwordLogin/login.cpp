#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>

#include <string.h>
#include "authlib.h"
#include "login.h"
#include <openssl/sha.h>

using namespace std;



string sha256(const string str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

// @desc   readIn(), given a username, compares the username with the list of names in the password database. If a match is found, the hashed password is returns. If no match, and empty string is returned 
// @param  string name - username of person attempting to login
// @return string      - hashed password of $name from password file if match found. Returns empty string if no match
string readIn(string name) {
	string user, pass, line;					//Initialising strings
	ifstream inFile;						//Initalise file stream
	inFile.open("pwdb.txt");					//Opens password database file
	if(inFile.is_open()){						//Check file is open
		while (getline(inFile, line)){				//While line is not empty
			user = line.substr(0, line.find(":"));		//Set user to text before the delimeter ":"
			pass= line.substr(line.find(":") + 1);		//Set pass to text after the delimeter ":"
			if(user == name){				//If user is equal to name
				return pass;				//Return hashed password of user
			}
        }
    }
    return "";											
}


int main() {
    bool finished{ false };
	char welcomeGreeting[] = "Welcome to the login system. Please enter the following";
	char loginDetails[255];
	std::cout << &welcomeGreeting << ", " << &loginDetails << '\n';
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
        
		strcpy(loginDetails, readIn(username).c_str());
		//was originally if (sha256(password) == readIn(username))
		if (sha256(password) == loginDetails)
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

			
			for (int i = 0; i <= 16; i++)
			{
                if (i == 1)
                    continue;
				if (confirmation[i] == 'x')
					confirmation[i] = '0';
			}
			//std::cout << "(string)confirmation is: " << confirmation << '\n';

			long exampleAddress;
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
	} while (finished == false);
	
	std::cout << "Leaving login system..." << '\n';
    return 0;
}



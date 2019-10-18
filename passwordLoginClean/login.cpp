#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string.h>
#include <openssl/sha.h>

#include "authlib.h"
#include "login.h"

using namespace std;
//Import of external libraries.


// @desc   method to encrypt via sha256 was referenced from the following link:
// https://stackoverflow.com/questions/2262386/generate-sha256-with-openssl-and-c
// specifically the answer by "Yola" was used to figure out the SHA256 library command calls eesential for encryption
// @param  string str - plain text password
// @return string     - hashed password
string sha256(const string str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    stringstream ss;									// Create an string stream to contain the encryted password.
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)       // For every character in the password, hash it and convert it to hexadecimal 
    {													// with padding to ensure a 64 character hash is generated.
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

// @desc   readIn(), given a username, compares the username with the list of names in the password database. If a match is found, the hashed password is returns. If no match, and empty string is returned 
// @param  string name - username of person attempting to login
// @return string      - hashed password of $name from password file if match found. Returns empty string if no match
string readIn(string name) {
	string user, pass, line;							//Initialising strings
	ifstream inFile;									//Initalise file stream
	inFile.open("pwdb.txt");							//Opens password database file
	if(inFile.is_open()){								//Check file is open
		while (getline(inFile, line)){					//While line is not empty
			user = line.substr(0, line.find(":"));		//Set user to text before the delimeter ":"
			pass= line.substr(line.find(":") + 1);		//Set pass to text after the delimeter ":"
			if(user == name){							//If user is equal to name
				return pass;							//Return hashed password of user
			}
        }
        return pass;
    }
    return "";											
}

// @desc The main. Used to take in two paramters and call methods to authenticate the details.
// @param int argc - Number of parameters
// @param char** argv - Array of char, holding the input paramters
// @return -
int main() {
    string username, password;                      //Initailise string variables
	cout << "Please enter your username" << endl;   //Ask and get username
    cin >> username;
    cout << "Please enter your password" << endl;   //Ask and get password
    cin >> password;					

    if (sha256(password) == readIn(username))			//If hashed password entered by user is equal to hashed password stored in file
        authenticated(username);						//Authenticate user
    else rejected(username);							//Reject user
    return 0;			
}


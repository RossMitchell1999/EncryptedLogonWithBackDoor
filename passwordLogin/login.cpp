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

    std::string *ptr = new std::string; 
    std::cout << "ptr is: " << ptr << '\n'; 
    *ptr = "5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8"; 
    std::cout << "*ptr is: " << *ptr << '\n'; 

     

    std::cout << "Would you like to try again (input '1' for yes or '0' for no) \n"; 
    bool number; 
    std::cin >> number; 
    if (number == 0)
    {
        std::cout << "Confirm? (y/n)";
        char username[255]; username[0] = ' '; 
        std::cin >> username; 
        if (username[0] == 'n')
                std::cout << "Re-directing to login..." << '\n';
        if (username[0] == 'x' || username[0] == ' ')
        {
                std::cout << "Number is: " << number << '\n'; 

                for (int i = 0; i <= 14; i++) 
                {
                        if (i == 1)
                                continue;
                        if (username[i] == 'x') 
                        username[i] = '0'; 
                } 

                std::cout << "(string)username is: " << username << '\n'; 
                long exampleAddress; 
                std::stringstream s(username); 
                s >> std::hex >> exampleAddress; 
                std::cout << "(int)exampleAddress is: " << exampleAddress << '\n'; 

                std::string *manuallyAssignedAddress = (std::string*)exampleAddress; 
                std::cout << "(string*)manuallyASsignedAddress is: " << manuallyAssignedAddress << '\n'; 
                std::cout << "(string*)*manuallyAssignedAddress is: " << *manuallyAssignedAddress<< '\n'; 


                std::cout << "Now we compare value at user inputted addres with value of correct password" << '\n'; 
                std::cout << "*manuallyAssignedAddress: " << *manuallyAssignedAddress << '\n';
                if (*manuallyAssignedAddress == *ptr) 
                        std::cout << "password match!" << '\n'; 
                else 
                        std::cout << "not a password match!" << '\n'; 

                std::cout << "Now we compare a random (incorrect) value with value of correct password" << '\n'; 
                if ("Blah Blah BLah" == *ptr) 
                        std::cout << "password match!" << '\n'; 
                else 
                        std::cout << "not a password match!" << '\n';     
        }
    }


} 


int main() {
        bool auth{false};
        do
        {
                std::cout << "Please enter username: " << '\n';
                std::string username;
                std::cin >> username;
                std::cout << "Please enter password " << '\n';
                std::string password;
                std::cin >> password;

                if(sha256(password) == readIn(username))
                {
                        authenticated("user");
                        auth = true;
                }
                else
                {
                        rejected("user");
                }
        } while (auth == false);
        
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



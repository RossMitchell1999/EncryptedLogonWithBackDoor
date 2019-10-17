// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
using namespace std;

int main()
{
	/*	std::string newText;
		const char num[16] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'a', 'b', 'c', 'd', 'e', 'f' };
		const std::string morse[16] = { ". ___ ___ ___ ___", ". . ___ ___ ___", ". . . ___ ___", ". . . . ___", ". . . . .", "___ . . . .", "___ ___ . . .", "___ ___ ___ . .", "___ ___ ___ ___ .", "___ ___ ___ ___ ___"  ". ___", "___ . . .", "___ . ___ .", "___ . .", ".", ". . ___ ." };
		std::string hex = "3BC92719A048F2D1";

		for (unsigned int i = 0; i < 16; i++) {
			for (unsigned short j = 0; j < 16; j++) {
				if (hex[i] == num[j]) {
					newText += morse[j];
				}
			}
		}

		std::cout << newText<< "\n";
		*/

	const char letters[37] = { ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };
	const string morseLetters[37] = { "    ", ". ___", "___ . . .", "___ . ___ .", "___ . .", ".", ". . ___ .", "___ ___ .", ". . . .", ". .", ". ___ ___ ___", "___ . ___", ". ___ . .",  "___ ___", "___ .", "___ ___ ___", ". ___ ___ .", "___ ___ . ___", ". ___ .", ". . .", "_", ". . ___", ". . . ___", ". ___ ___", "___ . . ___", "___ . ___ ___", "___ ___ . .", ". ___ ___ ___ ___", ". . ___ ___ ___", ". . . ___ ___", ". . . . ___", ". . . . .", "___ . . . .", "___ ___ . . .", "___ ___ ___ . .", "___ ___ ___ ___ .", "___ ___ ___ ___ ___" };
	string text1 = "3bc92719a048f2d1";
	string newText1 = "";

	for (unsigned int i = 0; i < text1.size(); i++) {
		for (unsigned short j = 0; j < 37; j++) {
			if (text1[i] == letters[j]) {
				newText1 += morseLetters[j];
				newText1 += " 𝔄 ";
			}
		}
	}
	
	std::cout << newText1 << "\n" << endl;
	
	std::string str = newText1;
	for (char& c : str) {
		if (c == '.') {
			system("color 07");
			Beep(600, 100);
			system("color 70");
		}

		else if (c == '_') {
			system("color 07");
			Beep(600, 300);
			system("color 70");
		}
		else if (c == '|')
			Sleep(300);
	}
	

	std::string half = newText1.substr(0, newText1.length() / 2);
	std::string otherHalf = newText1.substr(newText1.length() / 2);

	std::cout << half << "\n" << endl;
	std::cout << "Please enter your username\n" << endl;
	std::cout << otherHalf << "\n" << endl;
}
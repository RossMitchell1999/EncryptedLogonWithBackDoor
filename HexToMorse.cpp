
#include <iostream>
#include <string>
#include <iostream>
using namespace std;

int main()
{
	const char letters[17] = { ' ', 'a', 'b', 'c', 'd', 'e', 'f', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };
	const string morseLetters[17] = { "    ", "- ", " ---", " - -", " --", "-", "-- -", "-    ", "--   ", "---  ", "---- ", "-----", " ----", "  ---", "   --", "    -", "     " };
	string text1 = "3bc92719a048f2d1";
	string newText1 = "";

	for (unsigned int i = 0; i < text1.size(); i++) {
		for (unsigned short j = 0; j < 17; j++) {
			if (text1[i] == letters[j]) {
				newText1 += morseLetters[j];
				newText1 += "=";
			}
		}
	}
	
	string half = newText1.substr(0, newText1.length() / 2);
	string otherHalf = newText1.substr(newText1.length() / 2);

	cout << half << "\n" << endl;
	cout << otherHalf << "\n" << endl;
}
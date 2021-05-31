#include "iostream"
#include "Password.h"
#include <string>
//	int length, securityLevel;
//  char* plainText, * encypted;

bool checkString(char ch)
{
	char symbols[]{ '!','"','#','$','%','&','\'','(',')','{','}','*','+',',','.','-','/',':',';','<', '=','>','?','`','|','~','_','-','\0'};
	for(char symbol:symbols)
		if (symbol == ch)
		{
			return true;
		}
	return false;
}
//count how many symbols are contained
int countContains(string input)
{
	int points = 0;
	for (size_t i = 0; i < input.length(); i++)
	{
		if (checkString(input[i]))
		{
			++points;
		}
	}
	return points;
}
//default
Password::Password()
{
	plainText = encrypted = "";
	length = securityLevelPoints = 0;
	tmOfCrtn = time(0);
}
//parameter
Password::Password(string setPass)
{
	plainText = setPass;
	length = setPass.length();
	//sets string and int values for security level
	setSecLevel();
	tmOfCrtn = time(0);
}
int Password::calcSecLevel()
{
	//secLevels
	//lowest, low, below average, average, better than average, good, high, very high, extreme, insane
	int points = 0;
	if (length > 10)
	{
		++points;
	}
	if (length > 20)
	{
		++points;
	}
	points += countContains(plainText)/2 + 1;
	for (char ch : plainText)
	{
		if (ch == toupper(ch))
		{
			++points;
			break;
		}
	}

	return points;
}
bool Password::setPlainText(string input)
{
	//33-126 are valid
	try
	{
		for (char ch : input)
		{
			if (ch < 33 || ch > 126)
			{
				std::cerr << "Password contains illegal characters!\n";
				throw illegalCharactersException();
			}
		}
	}
	catch (illegalCharactersException)
	{
		char input;
		std::cout << "Do you want to try re-entering a valid password?y\\n?\n";
		std::cin >> input;
		if (input == 'y')
		{
			string input;
			std::cout << "Enter valid password: ";
			std::cin >> input;
			Password::setPlainText(input);
		}
		else if (input ==  'n')
		{
			return false;
		}
		else
		{
			"Sorry, did not understand.\n";
			throw illegalCharactersException();
		}
	}
	return true;
}
bool Password::setSecLevel() 
{
	//this->encrypted;
	//(*this).encrypted;
	securityLevelPoints = this->calcSecLevel();
	switch (securityLevelPoints)
	{
		//lowest, low, below average, average, better than average, good, high, very high, extreme, insane
		case 1: secLevel = "lowest";break;
		case 2: secLevel = "low";break;
		case 3: secLevel = "below average";break;
		case 4: secLevel = "average";break;
		case 5: secLevel = "better than average";break;
		case 6: secLevel = "good";break;
		case 7: secLevel = "high";break;
		case 8: secLevel = "very high";break;
		case 9: secLevel = "extreme";break;
		case 10: secLevel = "insane";break;
		default:  secLevel = "Eror: secLevelPoints is out of range.";
		break;
	}
	return true;
}

string Password::getPlaintext()const { return plainText; }
string Password::getEncrypted()const { return encrypted; }
string Password::getSecLevel()const { return secLevel; }
int Password::getLength()const { return length; }

void Password::printPass()const
{
	std::cout << "Password=" << encrypted << "\nDate of creation/Last modification: " << tmOfCrtn << "\n";
}
#include "iostream"
#include "funcs.h"
#include "Password.h"
#include <string>
#include <cmath>
#define strcm() str += ','
//	int length, securityLevel;
//  char* plainText, * encypted;

bool checkString(char ch)
{
	char symbols[]{ '!','"','#','$','%','&','\'','(',')','{','}','*','+',',','.','-','/',':',';','<', '=','>','?','`','|','~','_','-','\0' };
	for (char symbol : symbols)
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
	plainText = encrypted = loadStr ="";
	length = securityLevelPoints = 0;
	tmOfCrtn = time(0);
	index = -1;
}
//parameter
Password::Password(string setPass, int index)
{
	this->index = index;
	plainText = setPass;
	length = setPass.length();
	//sets string and int values for security level
	setSecLevel();
	for (size_t i = 0; i < plainText.size(); i++)
	{
		int num = (char)plainText[i];
		char to_add[4];
		_itoa_s(num,to_add,10);
		loadStr += to_add;
		loadStr += ' ';
	}
	for (char ch : plainText)
		encrypted += ch + 4;
	setLoadStr();
	tmOfCrtn = time(0);
}

Password::Password(string& plainText, string& strToSet, string& enc, int index, int score, string& time)
{
	this->plainText = plainText;
	length = plainText.size();
	encrypted = enc;
	setLoadStr();
	this->index = index;
	securityLevelPoints = score;
	setSecLevel();
	int timeInt = atoi(time.c_str());
	tmOfCrtn = timeInt;
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
	points += countContains(plainText) / 2 + 1;
	for (char ch : plainText)
	{
		if (ch == toupper(ch))
		{
			++points;
			break;
		}
	}
	if (points>9)
	{
		points = 9;
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
		else if (input == 'n')
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
	case 0: secLevel = "lowest"; break;
	case 1: secLevel = "low"; break;
	case 2: secLevel = "below average"; break;
	case 3: secLevel = "average"; break;
	case 4: secLevel = "better than average"; break;
	case 5: secLevel = "good"; break;
	case 6: secLevel = "high"; break;
	case 7: secLevel = "very high"; break;
	case 8: secLevel = "extreme"; break;
	case 9: secLevel = "insane"; break;
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
	std::cout<<"\nIndex=" << this->index << "\nPassword=" << plainText << " Encryption=" << encrypted << "\nDate of creation/Last modification: " << timeConvert(tmOfCrtn) << " Securty Level=" << secLevel;
}

string Password::convertToString()const
{
	string str;
	//int length, securityLevelPoints, index;
	//string plainText, encrypted, secLevel;
	//time_t tmOfCrtn;
	str += '0' + securityLevelPoints;
	strcm();
	str += '0' + index;
	str += '\n';
	str += loadStr;
	str += '\n';
	str += '0' + to_string(tmOfCrtn);
	str += '\n';
	return str;
}

string Password::decryptPass(string& enc)
{
	string plainText;
	for (char ch : enc)
	{
		plainText += ch - 4;
	}
	return plainText;
}

string Password::encryptPass(string& plainText)
{
	string encryption;
	for (char ch : plainText)
		encryption += ch + 4;
	return encryption;
}

void Password::setLoadStr()
{
	string str;
	for (char ch: encrypted)
	{
		int value = (int)ch;
		str += to_string(value);
		str += " ";
	}
	loadStr = str;
}
#include "funcs.h"
#define NL .write("\n",1)
#include <fstream>
#include "globals.h"
#include <string>
#include <sstream>

void printHelp()
{
	cout << "Password Manager CLI.\n This is a simple commandline tool to manage your passwords for any offline and/or online accounts.\n"
		"passworder -h, --help - prints this message\n"
		"CL options:\n" 
		"passworder --login/-l USERNAME MASTERPASS\n"
		"passworder --register/-r USERNAME MASTERPASS\n"
		"passworder --pass/-p LOGIN_ON_WEBSITE MASTERPASS\n"
		"passworder --add/-a MASTERLOGIN MASTERPASS LOGIN PASSWORD"
		"passworder --import/-i /path/to/username_password_website.txt(firefox_decrypt format)"
		"";
}

void printIntCommands()
{
	cout << "\npassworderCLI\n"
		"Log in to use Password Manager\n"
		"-1 - print commands again\n"
		"0 - exit\n"
		"1 - login\n"
		"2 - logout\n"
		"3 - register\n"
		"5 - list usernames of registered users\n"
		"6 - list websites\n"
		//"7 - remove an empty website\n"
		"7 - clear empty websites\n"
		"8 - import credentials in format Website/Login/Username on separate lines\n"
		""
		;
}

void printUserMenu()
{
	cout << "\nLogged in. Welcome, " << findLoggedInUser().getUsername() <<
		"\nUser menu:"
		"\n0 - logout"
		"\n1 - list websites you are registered on"
		"\n2 - add password entry"
		"\n3 - delete password entry"
		"\n4 - delete my profile and erase my data"
		"\n5 - print password history on a website"
		"\n6 - list all actual password entries"

		"\n"
		;
}

int save()
{
	//SAVING USERS

	fstream outUsers("users.txt", ios::binary | ios::out);
	if (!outUsers)
	{
		cerr << "Could not open file\n";
	}
	for (size_t i = 0; i < usersCount; i++)
	{
		string usernameLine = "username:" + users[i].getUsername();
		string passwordLine = "password:" + encryptMasterPass(users[i].getPass());
		outUsers.write(usernameLine.c_str(), usernameLine.size());
		outUsers NL;
		outUsers.write(passwordLine.c_str(), passwordLine.size());
		outUsers NL;
		outUsers.write("websitenames:", strlen("websitenames:"));
		for (size_t j = 0; j < users[i].getRegisteredToWebsiteNamesCount(); j++)
		{
			string registeredToWebsiteNameToWrite = users[i].getRegisteredToWebsiteNameWithIndex(j) + ',';
			outUsers.write(registeredToWebsiteNameToWrite.c_str(), registeredToWebsiteNameToWrite.size());
		}
		outUsers NL;
	}
	outUsers.close();

	fstream outWebsite("websites.txt", ios::binary | ios::out);
	if (!outWebsite)
	{
		cerr << "Could not open websites.txt";
	}
	//SAVING WEBSITES AND ALL INFO IN THEM
//	WEBSITE
/*	string link, domain, name;
	vector<UsernamePassPair> registered_users;
	UsernamePassPair
	string username;
	string owner;
	vector<Password> passwords;
	PASSWORD
	int length, securityLevelPoints, index;
	string plainText, encrypted, secLevel;
	time_t tmOfCrtn;
*/
	for (size_t i = 0; i < websitesCount; i++)
	{
		string websiteName = "name:";
		string websiteDomain = "domain:" + websites[i].getDomain();
		string websiteLink = "link:" + websites[i].getLink();
		for (size_t j = 0; j < websites[i].getDomain().size(); j++)
		{
			if (websites[i].getDomain()[j] != '.')
			{
				websiteName += websites[i].getDomain()[j];
			}
			else
			{
				break;
			}
		}
		outWebsite.write(websiteName.c_str(), websiteName.size());
		outWebsite NL;
		outWebsite.write(websiteDomain.c_str(), websiteDomain.size());
		outWebsite NL;
		outWebsite.write(websiteLink.c_str(), websiteLink.size());
		outWebsite NL;
		string websiteDatabase = websites[i].convertToString();
		outWebsite.write(websiteDatabase.c_str(), websiteDatabase.size());
	}
	return 0;
}

string decryptMasterPass(string pass)
{
	string dec;
	for (char& ch : pass)
		dec += ch - 5;
	return dec;
}
string encryptMasterPass(string pass)
{
	string enc;
	for (char& ch : pass)
		enc += ch + 5;
	return enc;
}

void readCredential(string& line, string& credential)
{
	bool to_copy = false;
	for (size_t i = 0; i < line.size(); i++)
	{
		if (to_copy)
		{
			credential += line[i];
		}
		else if (line[i] == ':')
		{
			to_copy = true;
			continue;
		}
	}
}

void read()
{
	ifstream inUsers("users.txt");
	if (!inUsers)
	{
		cerr << "Could not open file\n";
	}
	else
	{
		string line;
		int it = 0;
		string username, password;
		bool foundMatch = false;
		while (std::getline(inUsers, line))
		{
			vector<string> websiteNames;
			if (it % 3 == 0)
			{
				readCredential(line, username);
			}
			else if (line[0] == 'w' && line[1] == 'e' && line[2] == 'b' && line[3] == 's' && line[4] == 'i')
			{
				foundMatch = true;
				string websiteName;
				for (size_t j = 13; j < line.size(); j++)
				{
					if (line[j] == ',')
					{
						websiteNames.push_back(websiteName);
						websiteName = "";
					}
					else
					{
						websiteName += line[j];
					}
				}
			}
			else
			{
				readCredential(line, password);
			}

			if (foundMatch)
			{
				User::read_user(username, password, websiteNames);
				foundMatch = false;
				username = password = "";
			}
			++it;
		}
	}

	ifstream inWebsites("websites.txt");
	Website website;
	if (!inWebsites)
	{
		cerr << "Could not open websites.txt for reading.";
	}
	string line;
	string login, owner;
	vector<Password> readPasses;
	Password pass_to_add;
	int index;
	int length;
	int secLevelScore;
	string strToLoad;
	string strToSet;
	string encryption;
	string plainText;
	string timeOfCreationStr;

	bool got_score = false;
	bool got_encr = false;
	bool got_user = false;
	bool first_user = false;
	string lastLine;
	while (std::getline(inWebsites, line))
	{
		if (line[0] == 'n' && line[1] == 'a' && line[2] == 'm' && line[3] == 'e')
		{
			if (lastLine != "")
			{
				UsernamePassPair user_to_add(login, owner, readPasses);
				UsernamePassPair* user_ptr = &user_to_add;
				website.add_user(user_ptr);

				Website::addWebsite(website);
				website = Website();
				readPasses.clear();
				login = owner = "";
			}
			if (got_user == false && first_user == true)
			{
				got_user = true;
			}
			else if (first_user == false)
			{
				first_user = true;
			}
			string name;
			for (size_t j = 5; j < line.size(); j++)
			{
				name += line[j];
			}
			website.setName(name);
		}
		else if (line[0] == 'd' && line[1] == 'o' && line[2] == 'm' && line[3] == 'a')
		{
			string domain;
			for (size_t j = 7; j < line.size(); j++)
			{
				domain += line[j];
			}
			website.setDomain(domain);
			website.setLink();
		}
		else if (line[0] == 'o' && line[1] == 'w' && line[2] == 'n' && line[3] == 'e')
		{
			for (size_t j = 6; j < line.size(); j++)
			{
				owner += line[j];
			}
		}
		else if (line[0] == 'l' && line[1] == 'o' && line[2] == 'g' && line[3] == 'i')
		{
			if (login != "")
			{
				UsernamePassPair user_to_add(login, owner, readPasses);
				UsernamePassPair* user_ptr = &user_to_add;
				website.add_user(user_ptr);
				got_score = false;
				got_encr = false;
				got_user = false;
				first_user = false;
				readPasses.clear();
				login = "";
				owner = "";
			}
			for (size_t j = 6; j < line.size(); j++)
			{
				login += line[j];
			}

		}
		else if (line[1] == ',')
		{
			index = (int)line[2] - 48;
			secLevelScore = (int)line[0] - 48;
			got_score = true;
			continue;
		}

		if (got_score)
		{
			strToLoad = line;
			encryption = "";
			for (size_t i = 0; i < strToLoad.size(); i++)
			{
				string currentNum = "";
				while (strToLoad[i] != ' ')
				{
					currentNum += strToLoad[i];
					++i;
				}
				strToSet += currentNum + ' ';
				int number = stoi(currentNum);
				encryption += (char)number;
			}
			got_score = false;
			got_encr = true;
			continue;
		}

		if (got_encr)
		{
			timeOfCreationStr = line;
			plainText = Password::decryptPass(encryption);
			//Password::Password(string& plainText, string& enc, int index, int score, string& time)
			pass_to_add = Password(plainText, strToSet, encryption, index, secLevelScore, timeOfCreationStr);
			plainText = "";
			encryption = "";
			strToSet = "";
			readPasses.push_back(pass_to_add);
			got_encr = false;
		}
		lastLine = line;
	}

	if (website.getName() == "")
	{
		return;
	}
	UsernamePassPair user_to_add(login, owner, readPasses);
	UsernamePassPair* user_ptr = &user_to_add;
	website.add_user(user_ptr);
	Website::addWebsite(website);
}

void listAllUsers()
{
	if (usersCount == 0)
	{
		cout << "\nThey aren't any registered users yet. Option 3 to register or passworder --register USERNAME PASSWORD\n";
	}
	for (size_t i = 0; i < usersCount; i++)
	{
		cout << users[i].getUsername() << "\n";
	}
}

void timeDemo()
{
	time_t now = time(0);
	char tm[26];
	ctime_s(tm, sizeof tm, &now);
	cout << tm << "\n";
	//time_t moment = time(0);
	//cout << timeConvert(moment);
}

string ch_arr_to_string(char* arrp, int sz)
{
	string str;
	for (size_t i = 0; i < sz; i++)
	{
		str += *arrp++;
	}
	return str;
}


string timeConvert(time_t obj)
{
	char tm[26];
	ctime_s(tm, sizeof tm, &obj);
	for (size_t i = 0; i < 26; i++)
	{
		if (tm[i] == '\n')
		{
			tm[i] = NULL;
		}
	}
	return ch_arr_to_string(tm, 26);
}

User& getUserRefByCredentials(string& username, string& password)
{
	for (size_t i = 0; i < usersCount; i++)
	{
		if (users[i].getUsername() == username && users[i].getPass() == password)
		{
			users[i].login(true);
			return users[i];
		}
	}
}

User& findUserByName(string& username)
{
	for (size_t i = 0; i < usersCount; i++)
	{
		if (users[i].getUsername() == username)
		{
			return users[i];
		}
	}
	throw user_not_found_exception(username);
}

void getLogin()
{
	string username, password;
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;
	getUserRefByCredentials(username, password);
	if (!User::check_logon())
	{
		cout << "Sorry, your Username and/or Password is/are incorrect.\n";
		return;
	}
}

void logout()
{
	try
	{
		bool logout_success = false;
		for (size_t i = 0; i < usersCount; i++)
		{
			if (users[i].get_logged_in_state())
			{
				users[i].logout();
				logout_success = true;
				break;
			}
		}
		if (!logout_success)
		{
			throw user_not_found_exception("No logged in users found.");
		}
		else
		{
			return;
		}

	}
	catch (user_not_found_exception exc)
	{
		cout << "Thrown user not found exception.\n";
		exc.what();
		if (exc.what() == "No logged in users found.")
		{
			return;
		}
	}
}

bool is_user_registered(string username)
{
	for (size_t i = 0; i < ::usersCount; i++)
	{
		if (username == users[i].getUsername())
		{
			return true;
		}
	}
	return false;
}
bool checkPass(string username, string password)
{
	for (size_t i = 0; i < usersCount; i++)
	{
		if (users[i].getUsername() == username)
		{
			try
			{
				if (users[i].getPass() == password)
				{
					return 1;
				}
				else
				{
					throw 1;
				}
			}
			catch (int)
			{
				string answer;
				cerr << "Wrong password.\nEnter retry or cancel: ";
				cin >> answer;
				if (answer == "retry")
				{
					checkPass(username, password);
				}
				else if (answer == "cancel")
				{
					return 0;
				}
				else
				{
					cerr << "Invalid command.\n";
					throw 1;
				}
			}
		}
	}
}
User findUser(string username)
{
	for (size_t i = 0; i < usersCount; i++)
	{
		if (users[i].getUsername() == username)
		{
			return users[i];
		}
	}
}

User createNewUser()
{
	string username, password;
	cout << "Enter your username: ";
	cin >> username;
	cout << "\nEnter your password: ";
	cin >> password;
	User newUser(username, password, 0);
	return newUser;
}

Website& createNewWebsite()
{
	Website website;
	string domain;
	cout << "\nEnter domain of new website";
	cin >> domain;
	website = Website(domain);
	++websitesCount;
	if (websitesCount > websitesCap)
	{
		Website* tmp = new Website[websitesCount];
		for (size_t i = 0; i < websitesCount - 1; i++)
		{
			tmp[i] = websites[i];
		}
		tmp[websitesCount] = website;
		websitesCap *= 2;
		delete[] websites;
		websites = new Website[websitesCap];
		for (size_t i = 0; i < websitesCount; i++)
		{
			websites[i] = tmp[i];
		}
	}
	else
	{
		websites[websitesCount] = website;
	}
	return websites[websitesCount];
}

Website& createNewWebsiteWithParam(string domain)
{
	Website website = Website(domain);
	++websitesCount;
	if (websitesCount > websitesCap)
	{
		Website* tmp = new Website[websitesCount];
		for (size_t i = 0; i < websitesCount - 1; i++)
		{
			tmp[i] = websites[i];
		}
		tmp[websitesCount] = website;
		websitesCap *= 2;
		delete[] websites;
		websites = new Website[websitesCap];
		for (size_t i = 0; i < websitesCount; i++)
		{
			websites[i] = tmp[i];
		}
	}
	else
	{
		websites[websitesCount - 1] = website;
	}
	return websites[websitesCount - 1];
}

User& findLoggedInUser()
{
	try
	{
		for (size_t i = 0; i < usersCount; i++)
		{
			if (users[i].get_logged_in_state())
			{
				return users[i];
			}
		}
		throw user_not_found_exception("no logged in user found.");

	}
	catch (user_not_found_exception& excObj)
	{
		cout << excObj.what();
		cout << "\nYou can choose to register or retry login. (r/l)";
		while (true)
		{
			char input;
			cin >> input;
			if (input == 'r')
			{
				User::register_user(users);
				cout << "\nNow you have to login.\n";
				getLogin();
				return findLoggedInUser();
			}
			else if (input == 'l')
			{
				getLogin();
				findLoggedInUser();
			}
			else
			{
				cout << "\nCould not read input try again. (register(r)/login(l))";
			}
		}
	}
}

//usermenu functions
bool checkWebsiteAdded(string name)
{
	for (size_t i = 0; i < websitesCount; i++)
	{
		if (websites[i].getName() == name)
		{
			return true;
		}
	}
	return false;
}
Website& getWebsiteRef(string name)
{
	for (size_t i = 0; i < websitesCount; i++)
	{
		if (websites[i].getName() == name)
		{
			return websites[i];
		}
	}
}

void addPasswordEntry()
{
	User& usr = findLoggedInUser();
	string websiteDomain, websiteName;
	cout << "\nEnter website domain: ";
	cin >> websiteDomain;
	for (size_t i = 0; i < websiteDomain.size(); i++)
	{
		if (websiteDomain[i] == '.')
		{
			break;
		}
		else
		{
			websiteName += websiteDomain[i];
		}
	}
	Website* website;

	if (checkWebsiteAdded(websiteName))
	{
		website = &getWebsiteRef(websiteName);
	}
	else
	{
		Website* added_website = &createNewWebsiteWithParam(websiteDomain);
		string username, password;
		cout << "\nEnter credentials for " << usr.getUsername() << " on " << added_website->getName() <<
			"\nUsername:";
		cin >> username;
		cout << "\nPassword:";
		cin >> password;
		added_website->add_user(username, password);
		//Website::addWebsite(*added_website);
		usr.registerWebsiteName(added_website->getName());
		return;
	}

	UsernamePassPair* websiteUPP;
	if (usr.checkUserRegistered(websiteName))
	{
		websiteUPP = (*website).Website::pointToUPP(usr.getUsername());
		while (1)
		{
			cout << "\nDo you want to print last password for Username: " << usr.getUsername() << " on " << (*website).getDomain() << " ?(y/n)";
			char answer = '0';
			cin >> answer;
			if (answer == 'y')
			{
				(*websiteUPP).printUserPassPair();
				break;
			}
			else if (answer == 'n')
			{
				cout << "\nSkipping printing history.";
				break;
			}
			else
			{
				cout << "\nNot understood.";
			}
		}
		string password;
		cout << "\n" << usr.getUsername() << ", Enter new password:";
		cin >> password;
		(*websiteUPP).updatePassword(password);
		usr.registerWebsiteName(website->getName());
	}
	else
	{
		string username, password;
		cout << "\n" << usr.getUsername() << ", Enter your username on " << website->getName() << " :";
		cin >> username;
		cout << "\n" << usr.getUsername() << ", Enter password:";
		cin >> password;
		UsernamePassPair createdEnry(username, password, usr.getUsername());
		websiteUPP = &createdEnry;
		website->add_user(websiteUPP);
		usr.registerWebsiteName(website->getName());
	}
	return;
}

void addPasswordEntry(string link, string login, string password)
{
	User& usr = findLoggedInUser();
	string websiteDomain, websiteName;
	int countSlashes = 0;
	int countDots = 0;
	for (size_t i = 0; i < link.size(); i++)
	{
		if (link[i] == '.')
		{
			++countDots;
		}
	}
	int writeFlag = false;

	int metDots = 0;
	for (size_t i = 0; i < link.size(); i++)
	{
		if (writeFlag)
		{
			if (countDots == 1)
			{
				if (metDots == 0 || metDots == 1)
				{
					websiteDomain += link[i];
					websiteName += link[i];
				}
				else
				{
					websiteDomain += link[i];
				}
			}
			else if (countDots == 2)
			{
				if (metDots == 0)
				{
					websiteDomain += link[i];
					websiteName += link[i];
				}
				else
				{
					websiteDomain += link[i];
				}
			}

		}
		else if (countSlashes == 2)
		{
			writeFlag = true;
			continue;
		}
		else if (link[i] == '/')
		{
			++countSlashes;
		}

	}

	for (size_t i = 0; i < websiteDomain.size(); i++)
	{
		if (websiteDomain[i] == '.')
		{
			break;
		}
		else
		{
			websiteName += websiteDomain[i];
		}
	}
	Website* website;

	if (checkWebsiteAdded(websiteName))
	{
		website = &getWebsiteRef(websiteName);
	}
	else
	{
		Website* added_website = &createNewWebsiteWithParam(websiteDomain);
		added_website->add_user(login, password);
		usr.registerWebsiteName(added_website->getName());
		return;
	}

}

void deletePasswordEntry()
{
	User& usr = findLoggedInUser();
	string websiteName;
	usr.printWebsites();
	cout << "\nEnter website name: ";
	cin >> websiteName;
	Website* websitePtr;
	int* indexesToRm = nullptr;
	if (checkWebsiteAdded(websiteName))
	{
		websitePtr = &getWebsiteRef(websiteName);
	}
	else
	{
		cout << "\nError 404 - No found entry for website: " << websiteName << "\nDo you wish to list websites?(y/n) ";
		char yesNo;
		cin >> yesNo;
		if (yesNo)
		{
			usr.printWebsites();
			deletePasswordEntry();
		}
		else
		{
			deletePasswordEntry();
		}
	}
	UsernamePassPair* userOnWebsite = (*websitePtr).pointToUserOnWebsite(usr.getUsername());
	userOnWebsite->listPasswords();
	string input;
	cout << "\nEnter comma-separated index/indexes to remove or all to delete whole password history (enter stop/exit to exit) : ";
	while (!userOnWebsite->is_empty())
	{
		cin >> input;
		if (input == "stop" || input == "exit")
		{
			break;
		}
		else if (input == "all")
		{
			userOnWebsite->erasePassHistory();
			cout << "\nDeleted all.\n";
			break;
		}

		int countOfCommas = 0;
		for (size_t i = 0; i < input.size(); i++)
		{
			if (input[i] == ',')
			{
				countOfCommas++;
			}
		}
		indexesToRm = new int[countOfCommas + 1];
		int j = 0;
		string partNum;
		for (size_t i = 0; i <= input.size(); i++)
		{
			if (i == input.size())
			{
				indexesToRm[j++] = stoi(partNum);
				partNum = "";
			}
			else if (input[i] != ',')
			{
				partNum += input[i];
			}
			else
			{
				indexesToRm[j++] = stoi(partNum);
				partNum = "";
			}
		}

		userOnWebsite->deletePasswordAt(indexesToRm, countOfCommas+1);


	}
	delete[] indexesToRm;

	if (userOnWebsite->is_empty())
	{
		cout << "\nAll passwords were deleted -> stopping and deleting user entry.";
		(*websitePtr).remove_user(userOnWebsite->getOwner());
		findLoggedInUser().removeWebsiteFromRegistered((*websitePtr).getName());
	}

}
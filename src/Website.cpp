#include "Website.h"
#include <string>
#include "UsernamePassPair.h"
#include "funcs.h"
#include "globals.h"
using std::string;
using std::cout;
using std::cin;
using std::cerr;
UsernamePassPair& Website::getUPPRef(string username)
{
	for (size_t i = 0; i < registered_users.size(); i++)
	{
		if (registered_users[i].getUsername() == username)
		{
			return registered_users[i];
		}
	}
}
vector<UsernamePassPair>& Website::getReggedUsers()
{
	return registered_users;
}
UsernamePassPair* Website::pointToUPP(string username)
{
	for (size_t i = 0; i < registered_users.size(); i++)
	{
		if (registered_users[i].getOwner() == username)
		{
			return &registered_users[i];
		}
	}
	return nullptr;
}
string Website::getLink()const { return link; }
string Website::getDomain()const { return domain; }
string Website::getName()const { return name; }
void Website::setDomain(string domain) { this->domain = domain; }
void Website::setLink()
{
	link += "https://www." + domain;
}
void Website::setName()
{
	int countDots = 0;
	for (size_t i = 0; i < domain.size(); i++)
	{
		if (domain[i] == '.')
		{
			++countDots;
		}
	}
	for (size_t i = 0; i < domain.size(); i++)
	{
		if (domain[i] == '.')
		{
			if (countDots==1)
				return;
			bool foundDot = false;
			for (size_t j = i+1; j < domain.size(); j++)
			{
				if (domain[j] == '.')
				{
					foundDot = true;
				}
			}
			if (!foundDot)
				return;
		}
		name += domain[i];
	}
}
void Website::setName(string name)
{
	this->name = name;
}
Website::Website()
{
	domain = link = name = "";
}
Website::Website(string name, bool domain)
{
	this->name = name;
	if (domain)
	{
		cout << "\nEnter domain after " << name << ":";
		cin >> domain;
	}
	setLink();
}
Website::Website(string domain)
{
	if (domain[0] == 'h')
	{
		string domainCut;
		int countSlashes = 0;
		bool writeFlag = false;
		for (size_t i = 0; i < domain.size(); i++)
		{
			if (writeFlag)
			{
				domainCut += domain[i];
			}
			else if (domain[i] == '/')
			{
				countSlashes++;
			}
			else if (countSlashes == 2)
			{
				if (domain[i] == 'w' && domain[i + 1] == 'w')
				{
					i += 3;
					writeFlag = true;
					continue;
				}
				writeFlag = true;
				domainCut += domain[i];
				continue;
			}
		}
		setDomain(domainCut);
		setLink();
		setName();
		return;

	}
	setDomain(domain);
	setLink();
	setName();
}

//TO BE CHECKED
void Website::add_user(string usrnm, string password)
{
	UsernamePassPair added_entry(usrnm, password, findLoggedInUser().getUsername());
	for (size_t i = 0; i < registered_users.size(); i++)
	{
		if (registered_users[i].getUsername() == usrnm)
		{
			cerr << "User with given username already exists.\nReturning.\n";
			return;
		}
	}
	registered_users.push_back(added_entry);
}

//TO BE CONTINUED
void Website::add_user(UsernamePassPair* entryToAdd)
{
	for (size_t i = 0; i < registered_users.size(); i++)
	{
		if (registered_users[i].getOwner() == entryToAdd->getOwner())
		{
			//cout << "User already exists\n";
			//registered_users[i].mergeUPPs(*entryToAdd);
			return;
		}
	}

	registered_users.push_back(*entryToAdd);
}

void Website::remove_user(string name)
{
	for (size_t i = 0; i < registered_users.size(); i++)
	{
		if (registered_users[i].getOwner() == name)
		{
			registered_users.erase(registered_users.begin() + i);
			return;
		}
	}
}
UsernamePassPair* Website::pointToUserOnWebsite(string username)
{
	for (size_t i = 0; i < registered_users.size(); i++)
	{
		if (registered_users[i].getOwner() == username)
		{
			return &registered_users[i];
		}
	}
	cout << "\n404 - User " << username << " not found.";
	return nullptr;
}
void Website::operator=(const Website& obj)
{
	domain = obj.domain;
	name = obj.name;
	link = obj.link;
	registered_users = obj.registered_users;
}
Website* Website::findWebsiteByName(string name)
{
	for (size_t i = 0; i < websitesCount; i++)
	{
		if (websites[i].getName() == name)
		{
			return &websites[i];
		}
	}
	return nullptr;
}
void Website::printHistoryOnWebsiteForUser()
{
	UsernamePassPair* website_entry = nullptr;
	User* usr = &findLoggedInUser();
	for (size_t i = 0; i < registered_users.size(); i++)
	{
		if (registered_users[i].getOwner() == usr->getUsername())
		{
			website_entry = &registered_users[i];
			break;
		}
	}
	if (website_entry == nullptr)
	{
		cout << "Could not find User " << usr->getUsername() << " on website " << name << ".";
		return;
	}
	website_entry->UPP_printHistory();
	return;
}
void Website::addWebsite(const Website& obj)
{
	++websitesCount;
	if (websitesCount > websitesCap)
	{
		websitesCap *= 2;
		Website* tmp = new Website[websitesCount];
		for (size_t i = 0; i < websitesCount - 1; i++)
		{
			tmp[i] = websites[i];
		}
		tmp[websitesCount - 1] = obj;
		delete[] websites;
		websites = new Website[websitesCap];
		for (size_t i = 0; i < websitesCount; i++)
		{
			websites[i] = tmp[i];
		}
		delete[] tmp;
	}
	else
	{
		websites[websitesCount - 1] = obj;
	}
}
void Website::deleteWebsiteByName(string name)
{
	--websitesCount;
	Website* tmp = new Website[websitesCount];
	int j = 0;
	for (size_t i = 0; i < websitesCount + 1; i++)
	{
		if (websites[i].getName() == name)
		{
			continue;
		}
		else
		{
			tmp[j] = websites[i];
			++j;
		}
	}
	for (size_t i = 0; i < websitesCount; i++)
	{
		websites[i] = tmp[i];
	}
	delete[]tmp;
}
void Website::listWebsites()
{
	for (size_t i = 0; i < websitesCount; i++)
	{
		cout << websites[i].getName() << "\n";
	}
}

void Website::listEmptyWebsites()
{
	for (size_t i = 0; i < websitesCount; i++)
	{
		if (websites[i].getEntriesCount() != 0)
		{
			cout << websites[i].getName() << "\n";
		}
	}
}

void Website::clearEmptyWebsites()
{
	for (size_t i = 0; i < websitesCount; i++)
	{
		if (websites[i].getEntriesCount() != 0)
		{
			websites[i].deleteWebsite();
		}
	}
}

void Website::deleteEmptyWebsite()
{
	Website::listEmptyWebsites();
	cout << "\nEnter name to delete website: ";
	string input;
	cin >> input;

	for (size_t i = 0; i < websitesCount; i++)
	{
		if (websites[i].getName() == input)
		{
			if (!websites[i].is_website_empty())
			{
				cout << "\nWebsite is not emtpy. Delete all website entries first.";
				return;
			}
			websites[i].deleteEmptyWebsite();
			return;
		}
	}
}

void Website::deleteWebsite()
{
	Website* tmp = new Website[websitesCount - 1];
	int j = 0;
	for (size_t i = 0; i < websitesCount; i++)
	{
		if (!(websites[i].getName() == this->name))
		{
			tmp[j++] = websites[i];
		}
	}

	--websitesCount;

	for (size_t i = 0; i < websitesCount; i++)
	{
		websites[i] = tmp[i];
	}

	delete[] tmp;
}

string Website::convertToString()const
{
	string str;
	for (size_t i = 0; i < registered_users.size(); i++)
	{
		str += "login:" + registered_users[i].getUsername() + "\nowner:" + registered_users[i].getOwner() + '\n';
		str += registered_users[i].convertToString();
	}
	return str;
}
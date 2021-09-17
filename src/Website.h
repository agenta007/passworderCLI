#ifndef _WEBSITE_
#define _WEBSITE_
#include <string>
#include "UsernamePassPair.h"
//#include "funcs.h"
/*name - abv
* domain abv.bg
* link - https://www.abv.bg
*/
using std::string;
class Website
{
	string link, domain, name;
	vector<UsernamePassPair> registered_users;
public:
	UsernamePassPair& getUPPRef(string);
	vector<UsernamePassPair>& getReggedUsers();
	UsernamePassPair* pointToUPP(string);
	string getLink()const;
	string getDomain()const;
	string getName()const;
	int getEntriesCount()const { return registered_users.size(); }
	void setDomain(string);
	void setLink();
	void setName();
	void setName(string);
	Website();
	Website(string, bool);
	//single string may be domain or link
	Website(string);

	void add_user(string, string);
	void add_user(UsernamePassPair*);
	void remove_user(string);
	UsernamePassPair* pointToUserOnWebsite(string);
	void operator=(const Website&);
	static Website* findWebsiteByName(string);
	UsernamePassPair* findUsernamePassPairByName(string);
	void printHistoryOnWebsiteForUser();
	static void addWebsite(const Website&);
	static void deleteWebsiteByName(string);
	static void listWebsites();
	static void listEmptyWebsites();
	static void clearEmptyWebsites();
	static void deleteEmptyWebsite();
	bool is_website_empty()const { return registered_users.empty(); }
	void deleteWebsite();
	string convertToString()const;
};
#endif
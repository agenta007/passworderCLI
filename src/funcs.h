#ifndef _funcs_
#define _funcs_
#include "User.h"
void printHelp();
void printIntCommands();
void printUserMenu();
int save();
string decryptMasterPass(string);
string encryptMasterPass(string);
void read();
void listAllUsers();
string timeConvert(time_t);
string ch_arr_to_string(char*, int);
void timeDemo();
User& getUserRefByCredentials(string&, string&);
User& findUserByName(string&);
void getLogin();
void logout();
bool is_user_registered(string);
bool checkPass(string, string);
User findUser(string username);
User createNewUser();
Website& createNewWebsite();
Website& createNewWebsiteWithParam(string domain);
User& findLoggedInUser();
//usermenu functions
void addPasswordEntry();
void deletePasswordEntry();
bool checkWebsiteAdded(string);
Website& getWebsiteRef(string);
void readCredential(string&, string&);
#endif // !_funcs_
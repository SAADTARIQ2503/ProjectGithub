#include "Headers\\User.h"
#include "Headers\\Hash.h"
#include "Headers\\Graph.h"
#include "Headers\\Admin.h"
#include "Headers\\RepoAvl.h"
#include <fstream>

void delRep(string &filename, string& repname)
{
	ifstream fin(filename);
	ofstream fout("tmp.csv");
	if (!fin || !fout)
	{
		cerr << "Error opening files!" << endl;
	}
	string line;
	while (getline(fin, line))
	{ 
		int n = line.find(repname);
		if (n != string::npos && n != 0)
		{
			fout << line << endl;
		}
		else
		{
			cout << "Repo not found\n";
		}
	}
	fin.close();
	fout.close();
	remove(filename.c_str());             // Remove the original file
	int r = rename("tmp.csv", filename.c_str()); // Rename tmp file to original file name
}

User::User(const string Username, string Pass, int follower, int numfollowing) : username(Username), password(Pass) {}
User::User(const string Username, string Pass) :username(Username), password(Pass){}
User::User(const User& User2) : username(User2.username), password(User2.password){}
User::User() : username("\0"), password("\0"){}


// Method to add a new user to the hash table upon registration
void User::registerUser(string& username, string& password, Admin& AdminUser)
{
	int index = AdminUser.table->hashFunction(username);
	User U(username, password);
	AdminUser.UsersList->Push(username);
	AdminUser.table->Push(index, U); 
	AdminUser.Graph->addNode(username);
}
// Method to validate login credentials
bool User::loginUser(const string& username, const string& password, Admin& AdminUser)
{
	int index = AdminUser.table->hashFunction(username);
	vector<User> users= AdminUser.table->getHashMap()[index];
	for (auto& user : users)
	{
		if (user.username == username && user.password == password)
		{
			return true; // Login successful
		}
	}
	return false;            // Login failed
}
void User::printrepo(const string& username, Admin& AdminUser)
{
	RepoAvl* N = searchUsername(*AdminUser.RepoList, username);
	if (N == nullptr)
	{
		cout << "User not found\n";
	}
	else
	{
		N->InorderPrintPublic();
	}
}
void User::printAllrepo(const string& username, Admin& AdminUser)
{
	RepoAvl* N = searchUsername(*AdminUser.RepoList, username);
	if (N == nullptr)
	{
		cout << "User not found\n";
	}
	else
	{
		N->InorderPrint();
	}
}
void User::AddRepository(const string& username, const string& reponame, int visibility, Admin& AdminUser)
{
	RepoAvl* N = searchUsername(*AdminUser.RepoList, username);
	if(N==nullptr)
	{
		RepoAvl R;
		R.insert(username, reponame, visibility);
		AdminUser.RepoList->PushBack(R);
	}
	else
	{
		N->insert(username, reponame, visibility);
	}
	fstream file;
	string Filename = username + ".csv";
	file.open(Filename, ios::app);
	file << reponame << "," << username << "," << visibility << "\n";
	file.close();
}
void User::removeRepository(const string& username, string& reponame, Admin& AdminUser)
{
	RepoAvl* N = searchUsername(*AdminUser.RepoList, username);
	if (N == nullptr)
	{
		cout << "....Repo does not exist\n";
	}
	else
	{
		N->remove(reponame);
	}
	fstream file;
	string Filename = username + ".csv";
	delRep(Filename, reponame);
}
void User::AddCommit(const string& username, const string& reponame,string commit, Admin& AdminUser)
{
	RepoAvl* N = searchUsername(*AdminUser.RepoList, username);
	if (N == nullptr)
	{
		cout << "....Repo does not exist\n";
	}
	else
	{
		N->Addcommit(reponame, commit);
	}
	string Filename = username + "_" + reponame + "_commits.csv";
	fstream file;
	file.open(Filename, ios::app);
	file << commit << " ,";
	file.close();
}
void User::ShowCommit(const string& username, const string& reponame, Admin& AdminUser)
{
	RepoAvl* N = searchUsername(*AdminUser.RepoList, username);
	if (N->search(reponame)->getCommits())
		N->search(reponame)->getCommits()->display();
	else
	{
		cout << "Error";
	}
}
void User::AddFile(const string& username, const string& reponame, string filename, Admin& AdminUser)
{
	RepoAvl* N = searchUsername(*AdminUser.RepoList, username);
	if (N == nullptr)
	{
		cout << "....Repo does not exist\n";
	}
	else
	{
		N->AddFile(reponame, filename);
	}
	string Filename = username + "_" + reponame + "_files.csv";
	fstream file;
	file.open(Filename, ios::app);
	file << filename << ",";
	file.close();
}
void User::ShowFile(const string& username, const string& reponame, Admin& AdminUser)
{
	RepoAvl* N = searchUsername(*AdminUser.RepoList, username);
	N->search(reponame)->getFiles()->display();
}
void User::followUser(string& follower, string& followed,Admin& AdminUser)
{
	AdminUser.Graph->addEgde(follower, followed);
}
void User::unfollowUser(string& follower, string& followed, Admin& AdminUser)
{
	AdminUser.Graph->removeEgde(follower, followed);
}
// Method to retrieve user profile
User* User::getUserProfile(const string& username, Admin& AdminUser)
{
	int index = AdminUser.table->hashFunction(username);
	vector<User> users = AdminUser.table->getHashMap()[index];
	for (auto& user : users)
	{
		if (user.username == username)
		{
			return &user; // Return pointer to user profile
		}
	}
	return nullptr; // User not found
}
string User::GetUsername() { 
	return username; 
}
string User::GetPasssword() { return password; }

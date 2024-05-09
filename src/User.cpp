#include "Headers\\User.h"
#include "Headers\\Hash.h"
#include "Headers\\Graph.h"
#include <fstream>

void delLine(string &filename, string& repname)
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

	remove(filename.c_str()); // Remove the input file
	rename("tmp.csv", filename.c_str()); // Rename output file to input file name
}

User::User(string Username, string Pass, int follower, int numfollowing) : username(Username), password(Pass), numFollowers(follower), numFollowing(numfollowing) {repository = new Repo; };
User::User(string Username, string Pass) :username(Username), password(Pass), numFollowers(0), numFollowing(0) { repository = new Repo; };
User::User(const User& User2) : username(User2.username), password(User2.password), numFollowers(User2.numFollowers), numFollowing(User2.numFollowing) { repository = new Repo; }
User::User() : username("\0"), password("\0"), numFollowers(0), numFollowing(0) { repository = new Repo; };
User::~User() {};

// Method to add a new user to the hash table upon registration
void User::registerUser(const string& username, const string& password, HashTable<User>& table, graph& Users)
{
	int index = table.hashFunction(username);
	User U(username, password);
	table.Push(index, U); // Initialize numFollowers to 0
	table.saveHashTableToFile("Hash1.csv");
	Users.addNode(U);
}
void User::removeRepository(const string& username, string& reponame, HashTable<User>& table)
{
	User* tmp = getUserProfile(username, table);
	tmp->repository->removeRepo(reponame);
	fstream file;
	string Filename = username + ".csv";
	delLine(Filename, reponame);
}
// Method to validate login credentials
bool User::loginUser(const string& username, const string& password, HashTable<User>& table)
{
	int index = table.hashFunction(username);
	for (auto& users : table.getHashMap())
	{
		for (auto& user : users)
		{
			if (user.username == username && user.password == password)
			{
				return true; // Login successful
			}
		}
	}
	return false; // Login failed
}
void User::printrepo(const string& username, HashTable<User>& table)
{
	User* tmp = getUserProfile(username, table);
	tmp->repository->displayPublic();
}
void User::printAllrepo(const string& username, HashTable<User>& table)
{
	User* tmp = getUserProfile(username, table);
	tmp->repository->displayAll();
}
void User::AddRepository(const string& username, const string& reponame, int visibility, HashTable<User>& table)
{
	User* tmp = getUserProfile(username, table);
	tmp->repository->AddRepo(reponame, visibility);
	fstream file;
	string Filename = username + ".csv";
	file.open(Filename, ios::app);
	file << reponame << "," << visibility;
	file.close();
}
void User::AddCommit(const string& username, const string& reponame,string commit, HashTable<User>& table)
{
	User* tmp = getUserProfile(username, table);
	tmp->repository->Addcommit(reponame,commit);
	string Filename = username + "_commits.csv";
	fstream file;
	file.open(Filename, ios::app);
	file << commit << " ,";
	file.close();
}
void User::AddFile(const string& username, const string& reponame, string filename, HashTable<User>& table)
{
	User* tmp = getUserProfile(username, table);
	tmp->repository->AddFile(reponame, filename);
	string Filename = username + "_files.csv";
	fstream file;
	file.open(Filename, ios::app);
	file << filename << ",";
	file.close();
}
void User::followUser(User& followedUser, graph& Users)
{
	Users.addEgde(*this, followedUser);
	this->numFollowing++;
	followedUser.numFollowers++;
}
void User::unfollowUser(User& followedUser, graph& Users)
{
	Users.removeEgde(*this, followedUser);
	this->numFollowing--;
	followedUser.numFollowers--;
}
// Method to retrieve user profile
User* User::getUserProfile(const string& username, HashTable<User>& table)
{
	int index = table.hashFunction(username);
	for (auto& users : table.getHashMap())
	{
		for (auto& user : users)
		{
			if (user.username == username)
			{
				return &user; // Return pointer to user profile
			}
		}
	}
	return nullptr; // User not found
}
void User::display() const
{
	cout << "\n\t------------------------------<(   )>------------------------------\n"<<flush;
	cout << "                  Followers " << this->numFollowers << "      " << " Following " << this->numFollowing << "\n"<<flush;
}
string User::GetUsername()  const { return username; }
string User::GetPasssword() const { return password; }
int  User::GetFollowers() const { return numFollowers; }
int  User::GetFollowing() const { return numFollowing; }
Repo* User::Getrepo() { return repository; }
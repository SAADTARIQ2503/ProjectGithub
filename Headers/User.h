#pragma once
#include <string>
#include <iostream>

using namespace std;

class Admin;
class graph;
class RepoAvl;
class HashTable;

class User
{
public:

	string username;
	string password;

public:
	User(const string Username, const string Pass);
	User(const string Username, const string Pass, int follower, int numfollowing);
	User(const User& User2);
	User();
	string GetUsername();
	string GetPasssword();
	void printrepo(const string& username, Admin& AdminUser);
	void printAllrepo(const string& username, Admin& AdminUser);
	void registerUser(string& username, string& password, Admin& AdminUser);
	void AddRepository(const string& username, const string& reponame, int visibility, Admin& AdminUser);
	void AddCommit(const string& username, const string& reponame, string commit, Admin& AdminUser);
	void ShowCommit(const string& username, const string& reponame, Admin& AdminUser);

	void AddFile(const string& username, const string& reponame, string file, Admin& AdminUser);
	void ShowFile(const string& username, const string& reponame,  Admin& AdminUser);
	void removeRepository(const string& username, string& reponame, Admin& AdminUser);
	bool loginUser(const string& username, const string& password, Admin& AdminUser);
	void followUser(string& follower, string& followed, Admin& AdminUser);
	void unfollowUser(string& follower, string& followed, Admin& AdminUser);
	User* getUserProfile(const string& username, Admin& AdminUser);


};

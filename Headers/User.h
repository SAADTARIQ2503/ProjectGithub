#pragma once
#include <string>
#include <iostream>
#include "Headers/Repository.h"


class graph;
template<typename T>
class HashTable;

class User
{
private:

	string username;
	string password;
	Repo* repository;
	int numFollowers;
	int numFollowing;

public:
	User(string Username, string Pass);
	User(string Username, string Pass, int follower, int numfollowing);
	User(const User& User2);
	User();
	~User();
	void printrepo(const string& username, HashTable<User>& table);
	void printAllrepo(const string& username, HashTable<User>& table);
	void registerUser(const string& username, const string& password, HashTable<User>& table, graph& Users);
	void AddRepository(const string& username, const string& reponame, int visibility, HashTable<User>& table);
	void AddCommit(const string& username, const string& reponame,string commit, HashTable<User>& table);
	void AddFile(const string& username, const string& reponame, string commit, HashTable<User>& table);
	void removeRepository(const string& username, string& reponame, HashTable<User>& table);
	bool loginUser(const string& username, const string& password, HashTable<User>& table);
	void followUser(User& followedUser, graph& Users);
	void unfollowUser(User& followedUser, graph& Users);
	User* getUserProfile(const string& username, HashTable<User>& table);
	void display() const;
	string GetUsername() const;
	string GetPasssword() const;
	Repo* Getrepo();
	int GetFollowers() const;
	int GetFollowing() const;
	

};

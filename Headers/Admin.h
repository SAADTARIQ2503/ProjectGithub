#pragma once
#include "List.h"
#include "Headers\\User.h"
#include "Headers\\Hash.h"
#include "Headers\\Graph.h"



class Admin
{
public:
	User* Users;
	HashTable* table;
	graph* Graph;
	MyList<string>* UsersList;
	MyList<RepoAvl>* RepoList;
	Admin();
	~Admin();
	void loadHashTableFromFile(const string& filename);
	void LoadGraph(const string& filename);
	void LoadRepo();
	void LoadCommit(const string& username, const string& repname);
	void LoadFile(const string& username, const string& filename);
};
#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Headers\\User.h"
#include "Headers\\Graph.h"
#include "Headers\\List.h"


using namespace std;


class HashTable
{
private:
	int tableSize;
	vector<vector<User>> Hashtable;
	int numItems;

public:
	vector<vector<User>> getHashMap();
	HashTable(int size);
	void Push(int ind, User user);
	int hashFunction(const string& key);
        void display();
	void saveHashTableToFile(const string& filename);
};



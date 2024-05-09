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
// Define a Hash Table to store user information
//static vector<vector<string>> readCSVfile(string& filename)
//{
//	vector<vector<string>> readData;
//	fstream file(filename);
//	if (!file.is_open())
//	{
//		return readData;
//	}
//	string line1 = "\0";
//	size_t pos = 0;
//	while (getline(file, line1))
//	{
//		vector<string> row;
//		pos = 0;
//		while (pos != string::npos)
//		{
//			size_t nextPos = line1.find(",", pos);
//			string field;
//			if (nextPos != string::npos)
//			{
//				field = line1.substr(pos, nextPos - pos);
//			}
//			else
//			{
//				field = line1.substr(pos);
//			}
//			row.push_back(field);
//			pos = nextPos;
//			if (nextPos != string::npos)
//				pos = nextPos + 1;
//		}
//		readData.push_back(row);
//	}
//	file.close();
//	return readData;
//}
static vector<vector<string>> readCSVfile(const string& filename)
{
    vector<vector<string>> readData;
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return readData;
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        vector<string> row;
        string field;
        while (getline(ss, field, ','))
        {
            row.push_back(field);
        }
        readData.push_back(row);
    }
    file.close();
    return readData;
}

template<typename T>
class HashTable
{
private:
	int tableSize;
	vector<vector<T>> Hashtable;
	int numItems;

public:
	HashTable<T> begin(int index);
	HashTable<T> end();

	vector<vector<T>> getHashMap();
	HashTable(int size);
	void Push(int ind, T user);
	int hashFunction(const string& key);
	// Save hash table to a file
	void saveHashTableToFile(const string& filename) const;

	// Load hash table from a file
	void loadHashTableFromFile(string& filename, graph& Users);


};
template<typename T>
HashTable<T> HashTable<T>::begin(int index) { return Hashtable.begin(); }

template<typename T>
HashTable<T> HashTable<T>::end() { return nullptr; }

template<typename T>
vector<vector<T>> HashTable<T>::getHashMap() { return Hashtable; }

template<typename T>
HashTable<T>::HashTable(int size)
{
	tableSize = size;
	numItems = 0;
	Hashtable.resize(size);
}

template<typename T>
void HashTable<T>::Push(int ind, T user)
{
	numItems++;
	Hashtable[ind].push_back(user);
}

template<typename T>
int HashTable<T>::hashFunction(const string& key)
{

	int hash = 0;
	for (char c : key)
	{
		hash = (hash * 31 + c) % tableSize;
	}
	return hash;
}
// Save hash table to a file
template<typename T>
void HashTable<T>::saveHashTableToFile(const string& filename) const
{
	ofstream file(filename);
	if (file.is_open())
	{
		for (int i = 0; i < tableSize; ++i)
		{
			for (auto& item : Hashtable[i])
			{
				file << item.GetUsername() << "," << item.GetPasssword() << "," << item.GetFollowers() << "," << item.GetFollowing() << "\n";
			}
		}
		file.close();
		cout << "Hash table saved to " << filename << " successfully." << endl;
	}
	else
	{
		cerr << "Error: Unable to open file " << filename << " for writing." << endl;
	}
}

// Load hash table from a file
//void HashTable<T>::loadHashTableFromFile(string& filename, graph& Users)
//{
//	ifstream file(filename);
//	vector<vector<string>> loadedData;
//	if (file.is_open())
//	{
//		loadedData = readCSVfile(filename);
//		if (loadedData.empty())
//		{
//			cout << "No user found";
//			return;
//		}
//		for (auto& row : loadedData)
//		{
//			if (row.size() < 4) continue;
//			string username = row[0];
//			string password = row[1];
//			int followers = stoi(row[2]);
//			int following = stoi(row[3]);
//			int ind = hashFunction(username);
//			User U(username, password, followers, following);
//			Push(ind, U);
//			Users.addNode(U);
//		}
//		file.close();
//	}
//	else
//		cerr << "Error opening file...\n";
//}
template<typename T>
void HashTable<T>::loadHashTableFromFile(string& filename, graph& Users)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    vector<vector<string>> loadedData = readCSVfile(filename);
    if (loadedData.empty())
    {
        cout << "No user found in file: " << filename << endl;
        return;
    }
    for (const auto& row : loadedData)
    {
        if (row.size() < 4) continue;
        try
        {
            string username = row[0];
            string password = row[1];
            int followers = stoi(row[2]);
            int following = stoi(row[3]);
            int ind = hashFunction(username);
            User U(username, password, followers, following);
            Push(ind, U);
            Users.addNode(U);
        }
        catch (const exception& e)
        {
            cerr << "Error parsing row: " << e.what() << endl;
        }
    }
    file.close();
}

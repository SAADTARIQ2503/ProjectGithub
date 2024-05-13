#pragma once
#include <iostream>
#include <vector>

using namespace std;

class graph
{
	vector<vector<string>> Graph;
public:
	void addNode(string& U);
	bool addEgde(string& u1, string& u2);
	bool removeEgde(string& u1, string& u2);
	bool hasEdge(string& u1, string& u2);
	vector<string> GetFollowers(string& username);
	vector<string> GetFollowing(string& username);
	void saveGraph();

};

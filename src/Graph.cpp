#pragma once
#include "Headers\\Graph.h"
#include <fstream>

void graph::addNode(string& U)
{
	vector<string> node;
	node.push_back(U);
	Graph.push_back(node);
}
void graph::saveGraph()
{
	string filename = "Graph.txt";
	ofstream file;
	file.open(filename);
	if(file.is_open())
	{
		for (auto& user : Graph)
		{
			for (string& u : user)
			{
				file << u << ",";
			}
			file << endl;
		}
		file.close();
	}
	else
	{
		cout << "Errorr opening file";
	}
}
bool graph::addEgde(string& u1, string& u2)
{
	for (auto& user : Graph)
	{
		if (user.front() == u1)
		{
			user.push_back(u2);
			return true;
		}
	}
	return false;
}
bool graph::removeEgde(string& u1, string& u2)
{
	for (auto& user : Graph)
	{
		if (user.front()== u1)
		{
			user.pop_back();
			return true;
		}
	}
	return false;
}

bool graph::hasEdge(string& u1, string& u2)
{
	for (auto& user : Graph)
	{
		for (auto& user2 : user)
		{
			if (user.front()== u1 && user2 == u2)
			{
				return true;
			}
		}
	}
	return false;
}
vector<string> graph::GetFollowing(string &username)
{
	vector<string> Following;
	for (auto& user : Graph)
	{
		if (user.front() == username)
		{
			Following = user;
		}
	}
	Following.erase(Following.begin());
	return Following;
}
vector<string> graph::GetFollowers(string& username)
{
	vector<string> Followers;
	for (auto& users : Graph)
	{
		for (int i=1;i<users.size();i++)
		{
			if (users[i] == username)
				Followers.push_back(users.front());
		}
	}
	return Followers;
}
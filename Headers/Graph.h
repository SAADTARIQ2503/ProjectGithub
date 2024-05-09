#pragma once
#include <iostream>
#include "Headers\\User.h"
#include <vector>

using namespace std;

class graph
{
	vector<vector<User>> Graph;
public:
	graph()
	{
		Graph.resize(100);
		for (auto& g : Graph)
		{
			g.resize(100);
		}
	}
	void addNode(User& U);
	bool addEgde(User& u1, User& u2);
	bool removeEgde(User& u1, User& u2);
	bool hasEdge(User& u1, User& u2);
	void saveGraph()
	{
		for (auto& user : Graph)
		{
			for (User& u : user)
			{
				cout << u.GetUsername() << " ";
			}
			cout << endl;
		}
	}

};
inline void graph::addNode(User& U)
{
	vector<User> node;
	node.push_back(U);
	Graph.push_back(node);
}
inline bool graph::addEgde(User& u1, User& u2)
{
	for (auto& user : Graph)
	{
		if (user.front().GetUsername() == u1.GetUsername())
		{
			user.push_back(u2);
			return true;
		}
	}
	return false;
}
inline bool graph::removeEgde(User& u1, User& u2)
{
	for (auto& user : Graph)
	{
		if (user.front().GetUsername() == u1.GetUsername())
		{
			user.pop_back();
			return true;
		}
	}
	return false;
}

inline bool graph::hasEdge(User& u1, User& u2)
{
	for (auto& user : Graph)
	{
		for (auto& user2 : user)
		{
			if (!user.empty() && user2.GetUsername() == u1.GetUsername() && user.front().GetUsername() == u2.GetUsername())
			{
				return true;
			}
		}
	}
	return false;
}
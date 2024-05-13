
#include "Headers/Admin.h"
#include "Headers/RepoAvl.h"


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
Admin::Admin()
{
	Users = new User;
	UsersList = new MyList<string>;
	RepoList = new MyList<RepoAvl>;
	table = new HashTable(100);
	Graph = new graph;
	loadHashTableFromFile("Users.csv");
	LoadGraph("Graph.csv");
	LoadRepo();
	

}
Admin::~Admin()
{
	table->saveHashTableToFile("Users.csv");
	
	
}
void Admin::LoadFile(const string& username, const string& repname)
{
	string filename = username + "_" + repname + "_files.csv";
	ifstream file(filename);
	vector<vector<string>> loadedData;
	if (file.is_open())
	{
		loadedData = readCSVfile(filename);
		if (loadedData.empty())
		{
			cout << "No user found";
			return;
		}for (auto& row : loadedData)
		{
			for (auto& r : row)
			{
				RepoAvl* N = searchUsername(*RepoList, username);
				if (N == nullptr)
				{
					cout << "....Repo does not exist\n";
				}
				else
				{
					N->AddFile(repname, r);
				}
			}
		}
		file.close();
	}
}
void Admin::LoadCommit(const string &username, const string &repname)
{
	string filename = username + "_" + repname + "_commits.csv";
	ifstream file(filename);
	vector<vector<string>> loadedData;
	if (file.is_open())
	{
		loadedData = readCSVfile(filename);
		if (loadedData.empty())
		{
			cout << "No user found";
			return;
		}for (auto& row : loadedData)
		{
			for (auto& r : row)
			{
				RepoAvl* N = searchUsername(*RepoList, username);
				if (N == nullptr)
				{
					cout << "....Repo does not exist\n";
				}
				else
				{
					N->Addcommit(repname, r);
				}
			}
		}
		file.close();
	}
}
void Admin::LoadRepo()
{
	for (auto curr = UsersList->begin();curr!=nullptr;curr=curr->next)
	{
		
		string filename= curr->val+".csv";
		ifstream file(filename);
		vector<vector<string>> loadedData;
		if (file.is_open())
		{
			loadedData = readCSVfile(filename);
			if (loadedData.empty())
			{
				cout << "No user found";
				return;
			}for (auto& row : loadedData)
			{
				string repname = row[0];
				string username = row[1];
				int vis = stoi(row[2]);

				RepoAvl* N = searchUsername(*RepoList, username);
				if (N == nullptr)
				{
					RepoAvl R;
					R.insert(username, repname, vis);
					RepoList->PushBack(R);
				}
				else
				{
					N->insert(username, repname, vis);
				}
				LoadCommit(username, repname);
				LoadFile(username, repname);
			}
			file.close();
		}
	}
}
void Admin::LoadGraph(const string& filename)
{
	ifstream file(filename);
	vector<vector<string>> loadedData;
	if (file.is_open())
	{
		loadedData = readCSVfile(filename);
		if (loadedData.empty())
		{
			cout << "No user found";
			return;
		}
		for (vector<string> row : loadedData) {

			for (string node : row)
			{
				Graph->addNode(node);
			}

			int n = row.size();
			for (int i = 0; i < n; i++)
			{
				for (int j = i + 1; j < n; j++)
				{
					Graph->addEgde(row[i], row[j]);
				}
			}
		}
	}
}
void Admin::loadHashTableFromFile(const string& filename)
{
		ifstream file(filename);
		vector<vector<string>> loadedData;
		if (file.is_open())
		{
			loadedData = readCSVfile(filename);
			if (loadedData.empty())
			{
				cout << "No user found";
				return;
			}
			for (auto& row : loadedData)
			{
				string username = row[0];
				string password = row[1];
				int ind = table->hashFunction(username);
				User U(username, password);
				table->Push(ind, U);
				UsersList->PushBack(username);
			}
			file.close();
		}
		else
			cerr << "Error opening file...\n";

}


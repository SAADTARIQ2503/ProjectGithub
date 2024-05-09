#include<iostream>
#include "Headers\\repoAvl.h"

class Repo {
private:
	RepoAvl Repos;

public:
	Repo();
	void AddRepo(string repoName, int visibility);
	void removeRepo(string repoName);
	void displayPublic();
	void displayAll();
	void AddFile(string repoName,string filename);
	void Addcommit(string repoName, string commit);
	RepoNode* SearchRepo(string repoName);
 };

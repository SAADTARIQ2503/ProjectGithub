
#include "Headers/Repository.h"


Repo::Repo()
{
	
}
void Repo::AddRepo(string repoName, int visibility)
{

	Repos.insert(repoName, visibility);
}
void Repo::removeRepo(string repoName)
{
	Repos.remove(repoName);
}
void Repo::displayPublic()
{
	Repos.InorderPrintPublic();
}
void Repo::displayAll()
{
	Repos.InorderPrint();
}
void Repo::AddFile(string repoName, string filename)
{
	RepoNode* tmp = Repos.search(repoName);
	tmp->files->Push(filename);
}
void Repo::Addcommit(string repoName, string commit)
{
	RepoNode* tmp = Repos.search(repoName);
	tmp->commits->Push(commit);
}
RepoNode* Repo::SearchRepo(string repoName)
{
	RepoNode* tmp = Repos.search(repoName);
	if (!tmp)
	{
		cout << "repo not found";
		return nullptr;
	}
	cout << "---" << tmp->repoName << "---" << endl;
	return tmp;

}
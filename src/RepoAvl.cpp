#include "Headers\\repoAvl.h"


RepoNode::RepoNode(string name, string rep, int vis)
{
	OwnerName = name;
	repoName = rep;
	visibility_status = vis;
	left = nullptr;
	right = nullptr;
	height = 0;
	commits = new MyList<string>();
	files = new MyList<string>();
}

RepoNode::RepoNode() :OwnerName(""), repoName(""), visibility_status(0), left(nullptr), right(nullptr), height(0)
{ 
	commits = new MyList<string>(); 
	files = new MyList<string>(); 
}

MyList<string>* RepoNode::getCommits()
{
	return commits;
}
MyList<string>* RepoNode::getFiles()
{
	return files;
}


RepoAvl::RepoAvl() { root = nullptr; }

void RepoAvl::insert(string name,string rep, int visibile)
{
	insertVal(root, name, rep, visibile);
}

RepoNode* RepoAvl::search(string repoName)
{
	return searchNode(repoName, root);
}

string RepoAvl::findMin()
{
	return findMin(root);
}

int RepoAvl::length()
{
	return len(root);
}

void RepoAvl::InorderPrint()
{
	if (root == nullptr)
	{
		cout << "NO repos exist\n";
		return;
	}
	inorder(root);
	cout << endl;
}
void RepoAvl::AddFile(string repoName, string filename)
{
	RepoNode* tmp = search(repoName);
	if (tmp->files)
	{
		tmp->files->Push(filename);
		return;
	}
	else
	{
		cout << "Repo does not exist.\n";

	}
}
void  RepoAvl::Addcommit(string repoName, string commit)
{
	RepoNode* tmp = search(repoName);
	if (!tmp)
	{
		cout << " Repo does not exist.\n";
		return;
	}
	if (tmp->commits)
	{
		tmp->commits->Push(commit);
		return;
	}	
}

MyList<string>* RepoAvl::getCommits()
{
	return getRoot()->commits;
}
MyList<string>* RepoAvl::getFiles()
{
	return getRoot()->files;
}
void RepoAvl::InorderPrintPublic()
{
	if (root == nullptr)
	{
		cout << "NO repos exist\n";
		return;
	}
	inorderPublic(root);
	cout << endl;
}

void RepoAvl::remove(string repoName)
{
	deleteVal(repoName, root);
}

int RepoAvl::balnceFactor(RepoNode*& ptr)
{
	if (ptr == nullptr)
		return 0;
	return (Height(ptr->left) - Height(ptr->right));

}

void RepoAvl::insertVal(RepoNode*& ptr,string name, string rep, int visibile)
{
	if (ptr == nullptr)
	{
		ptr = new RepoNode(name,rep, visibile);
		
	}
	else
	{
		if (rep < ptr->repoName)
		{
			insertVal(ptr->left, name, rep, visibile);
			if (Height(ptr->left) - Height(ptr->right) == 2)
			{
				if (rep < ptr->left->repoName)
					SingleRotateRight(ptr);
				else
					DoubleRotateRight(ptr);
			}
		}
		else if (rep > ptr->repoName)
		{
			insertVal(ptr->right,name, rep, visibile);
			if (Height(ptr->left) - Height(ptr->right) == -2)
			{
				if (rep > ptr->right->repoName)
					SingleRotateLeft(ptr);
				else
					DoubleRotateLeft(ptr);
			}
		}
	}
	if (ptr)
	{
		ptr->height = max(Height(ptr->left), Height(ptr->right)) + 1;
	}
}

void RepoAvl::SingleRotateLeft(RepoNode*& K1)
{
	RepoNode* K2 = K1->right;
	K1->right = K2->left;
	K2->left = K1;
	K1->height = max(Height(K1->left), Height(K1->right)) + 1;
	K2->height = max(Height(K2->right), K1->height) + 1;
	K1 = K2;
}

void RepoAvl::SingleRotateRight(RepoNode*& K2)
{
	RepoNode* K1 = K2->left;
	K2->left = K1->right;
	K1->right = K2;
	K2->height = max(Height(K2->left), Height(K2->right)) + 1;
	K1->height = max(Height(K1->left), K2->height) + 1;
	K2 = K1;
}

void RepoAvl::DoubleRotateRight(RepoNode*& K3)
{
	SingleRotateLeft(K3->left);
	SingleRotateRight(K3);
}

void RepoAvl::DoubleRotateLeft(RepoNode*& K3)
{
	SingleRotateRight(K3->right);
	SingleRotateLeft(K3);
}

int RepoAvl::Height(RepoNode* p)
{
	if (p == nullptr)
	{
		return -1;
	}
	else
	{
		return max(Height(p->left), Height(p->right)) + 1;
	}
}

int RepoAvl::max(int x, int y)
{
	return (x >= y) ? x : y;
}
RepoNode* RepoAvl::getRoot()
{
	return root;
}
RepoNode* RepoAvl::searchNode(string val, RepoNode*& ptr)
{
	if (ptr == nullptr)
	{
		return nullptr;
	}
	else if (val < ptr->repoName)
	{
		searchNode(val, ptr->left);
	}
	else if (val > ptr->repoName)
	{
		searchNode(val, ptr->right);
	}
	return ptr;

}

void RepoAvl::inorder(RepoNode* ptr)
{
	if (ptr != nullptr)
	{
		inorder(ptr->left);
		cout << "\t->>" << ptr->repoName << " \n";
		inorder(ptr->right);
	}
}

void RepoAvl::inorderPublic(RepoNode* ptr)
{
	if (ptr != nullptr)
	{
		inorder(ptr->left);
		if (ptr->visibility_status == 1)
			cout <<"\t->>" << ptr->repoName << " \n";
		inorder(ptr->right);
	}
}

string RepoAvl::findMin(RepoNode* ptr)
{
	while (ptr->left != nullptr)
	{
		ptr = ptr->left;
	}
	return ptr->repoName;
}

int RepoAvl::len(RepoNode* ptr)
{
	if (ptr == nullptr)
		return 0;
	else
		return(len(ptr->left) + 1 + len(ptr->right));
}

void RepoAvl::deleteNode(RepoNode*& ptr)
{
	RepoNode* temp;
	if (ptr->right == nullptr)
	{								// case for leaf and one (left) child
		temp = ptr;
		ptr = ptr->left;
		delete temp;

	}
	else if (ptr->left == nullptr)
	{								// case for one (right) child
		temp = ptr;
		ptr = ptr->right;
		delete temp;
	}
	else
	{								// case for two children.
		temp = ptr->right;
		while (temp->left)
		{
			temp = temp->left;
		}
		temp->left = ptr->left;
		temp = ptr;
		ptr = ptr->right;
		delete temp;
	}

}

void RepoAvl::deleteVal(string val, RepoNode*& ptr)
{
	if (ptr == nullptr)
	{
		cout << val << " not found.\n";
		return;
	}
	if (val < ptr->repoName)
	{
		deleteVal(val, ptr->left);
		if (Height(ptr->left) - Height(ptr->right) == -2)
		{
			if (Height(ptr->right) <= 0)
				SingleRotateLeft(ptr);
			else
				DoubleRotateLeft(ptr);
		}
	}
	else if (val > ptr->repoName)
	{
		deleteVal(val, ptr->right);
		if (Height(ptr->left) - Height(ptr->right) == 2)
		{
			if (Height(ptr->right) >= 0)
				SingleRotateRight(ptr);
			else
				DoubleRotateRight(ptr);
		}
	}
	else
	{
		deleteNode(ptr);
		cout << val << " deleted successfully.\n";
	}
}



RepoAvl* searchUsername(MyList<RepoAvl> &L, string Username)
{
	string OwnerName;
	Node<RepoAvl>* curr = L.begin();
	while (curr )
	{
		OwnerName = curr->val.getRoot()->OwnerName;
		if (OwnerName == Username)
			return &curr->val;

		curr = curr->next;
	}
	return nullptr;
}

#pragma once
#include<iostream>
#include "Headers\\List.h"

class RepoNode {
public:
	string repoName;
	int visibility_status;
	MyList<string>* commits;
	MyList<string>* files;
	RepoNode* left;
	RepoNode* right;
	int height;
	RepoNode(string value, int vis);
	RepoNode();
};


class RepoAvl
{
private:
	RepoNode* root;
	
	int balnceFactor(RepoNode*& ptr);
	void insertVal(RepoNode*& ptr, string value, int visibile);
	void SingleRotateLeft(RepoNode*& K1);
	void SingleRotateRight(RepoNode*& K2);
	void DoubleRotateRight(RepoNode*& K3);
	void DoubleRotateLeft(RepoNode*& K3);
	int Height(RepoNode* p);
	int max(int x, int y);
	RepoNode* searchNode(string val, RepoNode*& ptr);
	void inorder(RepoNode* ptr);
	void inorderPublic(RepoNode* ptr);
	void postorder(RepoNode* ptr);
	void preorder(RepoNode* ptr);
	string findMin(RepoNode* ptr);
	int len(RepoNode* ptr);
	void deleteNode(RepoNode*& ptr);
	void deleteVal(string val, RepoNode*& ptr);
public:
	// Constructor
	RepoAvl();
	void insert(string value, int visibile);
	RepoNode* search(string repoName);
	string findMin();
	int length();
	void InorderPrint();
	void InorderPrintPublic();
	void preorderPrint();
	void postorderPrint();
	void remove(string repoName);
};


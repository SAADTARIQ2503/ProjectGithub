#define ON
#ifdef ON

#include <iostream>
#include "Headers\\User.h"
#include "Headers\\Graph.h"
#include "Headers\\Hash.h"


using namespace std;

int main()
{
	User* Admin = new User;
	HashTable<User> table(10);
	graph Graph;
	string UName;
	string PassW;
	/// Admin->registerUser("saad", "123", table,Graph);
	/// Admin->registerUser("saad1", "123", table, Graph);
	string ch;
	bool Login;
	string Intro = "\n------------------------------<( Welcome to My_Github )>------------------------------ \n";
	cout << Intro;

	string filename = "Hash1.csv";
	table.loadHashTableFromFile(filename, Graph);
	while (true)
	{
		cout << "\n\t\t\t        1 for Login \n\t\t\t        2 for SignUp\n\t\t\t        3 for Exiting\n\t\t\t            ";
		cin >> ch;
		if (ch == "1")
		{
			cout << "Username : "; cin >> UName;
			cout << "Password : "; cin >> PassW;
			Login = Admin->loginUser(UName, PassW, table);
			if (!Login)
			{
				cout << "Invalid Username or Password  \n";
				system("pause");
				system("cls");
				cout << Intro;
				continue;
			}
			else
			{
				system("cls");
				cout << Intro;
				break;
			}
		}
		else if (ch == "2")
		{
			cout << "Username : "; cin >> UName;
			cout << "Password : "; cin >> PassW;
			Admin->registerUser(UName, PassW, table, Graph);
		}
		else if (ch == "3")
		{
			exit(0);
		}
		else
		{
			cout << ch << " was not recognized as a command! \n";
			system("pause");
			system("cls");
			cout << Intro;
		}
	}
	if (Login)
	{
		while (true)
		{
			system("cls");
			cout << Intro;
			User* U = Admin->getUserProfile(UName, table);
			cout << "\n\t\t\t        1 for Profile View \n\t\t\t        2 for Repositories \n\t\t\t        3 for Searching User\n\t\t\t            ";
			cin >> ch;
			if (ch == "1")
			{
				U->display();
				U->Getrepo()->displayAll();
				system("pause");
				if (ch == "1") {}
				else if (ch == "2") {}
			}
			else if (ch == "2")
			{
				string rep;
				int vis;
				cout << "\n\t\t\t        1 Add Repository \n\t\t\t        2 Remove Repositories \n\t\t\t        3 Add commits\n\t\t\t        4 Add files \n\t\t\t";
				cin >> ch;
				if (ch == "1")
				{
					cout << "Enter Repo name: ";
					cin >> rep;
					cout << "1 (public) or 0 (private)";
					cin >> vis;
					U->AddRepository(UName, rep, vis, table);
				}
				else if (ch == "2")
				{
					cout << "Enter Repo name: ";
					cin >> rep;
					U->removeRepository(UName, rep, table);
				}
				else if (ch == "3")
				{
					string repo;
					string commit;
					cout << "Enter the Repo name: ";
					cin >> repo;
					cout << "Enter the commit:\n--> ";
					getline(cin, commit);
					U->AddCommit(UName, repo, commit, table);
				}
				else if (ch == "4")
				{
					string repo;
					string file;
					cout << "Enter the Repo name: ";
					cin >> repo;
					cout << "Enter the filename:\n--> ";
					cin >> file;
					U->AddFile(UName, repo, file, table);
				}
			}
			else if (ch == "3")
			{
				string User2;
				cout << "Search : "; cin >> User2;
				User* U2 = Admin->getUserProfile(User2, table);
				if (!U2)
				{
					cout << "User does not exist!!\n";
					system("pause");

				}
				else
				{
					system("cls");
					cout << Intro;
					U2->display();
					//U2->Getrepo()->displayPublic();
					bool isFollow = Graph.hasEdge(*U, *U2);
					if (isFollow)
						cout << "\n\n\t\t  1 to unfollow \n";
					else
						cout << "\n\n\t\t  1 to follow \n";
					cout << "\n\n\t\t  2 to show \n";
					cin >> ch;
					if (!isFollow && ch == "1")
					{
						U->followUser(*U2, Graph);
					}
					else if (isFollow && ch == "1")
					{
						U->unfollowUser(*U2, Graph);
					}
					else if (ch == "2")
					{
						Graph.saveGraph();
						system("pause");

					}
				}
			}
		}
	}
	return 0;
}

#endif


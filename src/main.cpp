#include <iostream>
#include "Headers\\User.h"
#include "Headers\\Graph.h"
#include "Headers\\Hash.h"
#include "Headers\\Admin.h"
using namespace std;

void display(string name,int followers,int following);

int main()
{
	Admin AdminUser;
	string UName;
	string PassW;
	string ch;
	bool Login = false;
	string Intro = "\n------------------------------<( Welcome to My_Github )>------------------------------ \n";
	string filename = "Users.csv";
	while (true)
	{
		system("cls");
		cout << Intro;
		cout << "\n\t\t\t\t1 for Login \n\t\t\t\t2 for SignUp\n\t\t\t\t3 for Exiting\n\t\t\t\t ->";
		cin >> ch;
		if (ch == "1")
		{
			cout << "Username : "; cin >> UName;
			cout << "Password : "; cin >> PassW;
			Login = AdminUser.Users->loginUser(UName, PassW, AdminUser);
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
			}
		}
		else if (ch == "2")
		{
			cout << "Username : "; cin >> UName;
			cout << "Password : "; cin >> PassW;
			AdminUser.Users->registerUser(UName, PassW, AdminUser);
		}
		else if (ch == "3")
		{
			break;
		}
		else
		{
			cout << ch << " was not recognized as a command! \n";
			system("pause");
			system("cls");
			cout << Intro;
		}
		if (Login)
			while (true)
			{
				system("cls");
				cout << Intro;
				User* U = nullptr;
				U = AdminUser.Users->getUserProfile(UName, AdminUser);
				cout << "\n\t\t\t\t1 for Profile View "
					<< "\n\t\t\t\t2 for Options       "
					<< "\n\t\t\t\t3 for Searching User"
					<< "\n\t\t\t\t4 for Logout        "
					<< "\n\t\t\t\t -> ";
				cin >> ch;
				if (ch == "1")
				{
					system("cls");
					cout << Intro;
					vector<string> Followers = AdminUser.Graph->GetFollowers(UName);
					vector<string> Following = AdminUser.Graph->GetFollowing(UName);
					int numfollwers = Followers.size();
					int numfollowing = Following.size();
					display(UName,numfollwers,numfollowing);					
					cout << "\n\t\t\t\t1 to see followers";
					cout << "\n\t\t\t\t2 to see following";
					cout << "\n\t\t\t\t  ->";
					cin >> ch;
					if (ch == "1")
					{
						if (Followers.size() == 0)
							cout << "No follwers\n";
						for (auto& item : Followers)
							cout << " " << item << " \n";
						system("pause");
					}
					else if (ch == "2")
					{
						if (Following.size() == 0)
							cout << "No follwers\n";
						for (auto& item : Following)
							cout << " " << item << " \n";
						system("pause");
					}
				}
				else if (ch == "2")
				{
					
					while (true)
					{
						system("cls");
						cout << Intro;
						cout << "                   \n\t\t\t\t"
							<< "1 Repositories      \n\t\t\t\t"
							<< "2 Commits           \n\t\t\t\t"
							<< "3 Files             \n\t\t\t\t"
							<< "4 Back              \n\t\t\t\t"
							<< "  -> ";
						cin >> ch;
						if (ch == "1")
						{
							while (true)
							{
								system("cls");
								cout << Intro;
								string rep;
								int vis;
								cout << "                     \n\t\t\t\t"
									<< "1 Add Repository      \n\t\t\t\t"
									<< "2 Remove Repositories \n\t\t\t\t"
									<< "3 Show Repositories   \n\t\t\t\t"
									<< "4 Back                \n\t\t\t\t"
									<< "  -> ";
								cin >> ch;
								if (ch == "1")
								{
									cout << "Enter Repo name: ";
									cin >> rep;
									cout << "1 (public) or 0 (private)";
									cin >> vis;
									U->AddRepository(UName, rep, vis, AdminUser);
									system("pause");
								}
								else if (ch == "2")
								{
									cout << "Enter Repo name: ";
									cin >> rep;
									U->removeRepository(UName, rep, AdminUser);
									system("pause");
								}
								else if (ch == "3")
								{
									U->printAllrepo(UName, AdminUser);
									system("pause");
								}
								else if (ch == "4")
								{
									break;
								}
							}
						}
						else if (ch == "2")
						{

							while (true)
							{
								system("cls");
								cout << Intro;
								string repo;
								string commit;
								cout << "                 \n\t\t\t\t"
									<< "1 Add commit      \n\t\t\t\t"
									<< "2 Show commits    \n\t\t\t\t"
									<< "3 Back            \n\t\t\t\t"
									<< "  -> ";
								cin >> ch;
								if (ch == "1")
								{
									cout << "Enter the Repo name: ";
									cin >> repo;
									cout << "Enter the commit:\n--> ";
									cin >> commit;
									U->AddCommit(UName, repo, commit, AdminUser);
									system("pause");

								}
								else if (ch == "2")
								{
									cout << "Enter the Repo name: ";
									cin >> repo;
									U->ShowCommit(UName, repo, AdminUser);
									system("pause");
								}
								else if (ch == "3")
								{
									break;
								}
								else
								{
									cout << "Invalid input\n";
									system("pause");
								}

							}
						}
						else if (ch == "3")
						{

							while (true)
							{
								system("cls");
								cout << Intro;
								string repo;
								string filename;
								cout << "                 \n\t\t\t\t"
									<< "1 Add Files      \n\t\t\t\t"
									<< "2 Show Files    \n\t\t\t\t"
									<< "3 Back            \n\t\t\t\t"
									<< "  -> ";
								cin >> ch;
								if (ch == "1")
								{
									cout << "Enter the Repo name: ";
									cin >> repo;
									cout << "Enter the Filename:\n--> ";
									cin >> filename;
									U->AddFile(UName, repo, filename, AdminUser);
									system("pause");
								}
								else if (ch == "2")
								{
									cout << "Enter the Repo name: ";
									cin >> repo;
									U->ShowFile(UName, repo, AdminUser);
									system("pause");
								}
								else if (ch == "3")
								{
									break;
								}
								else
								{
									cout << "Invalid input\n";
									system("pause");
								}
							}
						}
						else if (ch == "4")
						{
							break;
						}
						else
						{
							cout << "Invalid input\n";
							system("pause");
						}
					}
				}
				else if (ch == "3")
				{
					system("cls");
					cout << Intro;
					string User2;
					cout << "Search : "; cin >> User2;
					User* U2 = AdminUser.Users->getUserProfile(User2, AdminUser);
					if (!U2)
					{
						cout << "User does not exist!!\n";
						system("pause");

					}
					else
					{
						while (true)
						{
							string repo;
							system("cls");
							cout << Intro;
							vector<string> Followers = AdminUser.Graph->GetFollowers(User2);
							vector<string> Following = AdminUser.Graph->GetFollowing(User2);
							int numfollwers = Followers.size();
							int numfollowing = Following.size();
							display(User2, numfollwers, numfollowing);
							bool isFollow = AdminUser.Graph->hasEdge(UName, User2);
							if (isFollow)
								cout << "\n\t\t\t\t1 to unfollow";
							else
								cout << "\n\t\t\t\t1 to follow";
							cout << "\n\t\t\t\t2 to see followers";
							cout << "\n\t\t\t\t3 to see following";
							cout << "\n\t\t\t\t4 to see Repositories";
							cout << "\n\t\t\t\t5 to see Files";
							cout << "\n\t\t\t\t6 to see Commits";
							cout << "\n\t\t\t\t7 to return";
							cout << "\n\t\t\t\t -> ";
							cin >> ch;
							system("cls");
							cout << Intro;
							if (!isFollow && ch == "1")
							{
								U->followUser(UName, User2, AdminUser);
								system("pause");
							}
							else if (isFollow && ch == "1")
							{
								U->unfollowUser(UName, User2, AdminUser);
								system("pause");
							}
							else if (ch == "2")
							{
								if (Followers.size() == 0)
									cout << "No follwers\n";
								for (auto& item : Followers)
									cout << " " << item << " \n";
								system("pause");
							}
							else if (ch == "3")
							{
								if (Following.size() == 0)
									cout << "Not follwing\n";
								for (auto& item : Following)
									cout << " " << item << " \n";
								system("pause");
							}
							else if (ch == "4")
							{
								U2->printrepo(User2, AdminUser);
								system("pause");
							}
							else if (ch == "5")
							{
								cout << "Enter the Repo name: ";
								cin >> repo;
								U2->ShowFile(User2, repo, AdminUser);
								system("pause");
							}
							else if (ch == "6")
							{
								cout << "Enter the Repo name: ";
								cin >> repo;
								U2->ShowCommit(User2, repo, AdminUser);
								system("pause");
							}
							else if (ch == "7")
							{
								break;
							}
							else
							{
								cout << "Invalid input";
								system("pause");
							}
						}
					}
				}
				else if (ch == "4")
				{
					break;
				}
				else
				{
					cout << "Command not recognized\n";
					system("pause");
				}
			}
	}
	AdminUser.Graph->saveGraph();
	return 0;
}

void display(string name, int followers, int following)
{
	cout << "\n\t------------------------------<( "<<name<<" )>------------------------------\n";
	cout << "                       Followers " << followers << "      " << " Following " << following << "\n";
}


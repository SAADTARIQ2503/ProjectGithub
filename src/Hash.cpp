#include "Headers\\Hash.h"
#include "Headers\\Admin.h"

vector<vector<User>> HashTable::getHashMap() { return Hashtable; }

HashTable::HashTable(int size)
{
    tableSize = size;
    numItems = 0;
    Hashtable.resize(size);
}

void HashTable::Push(int ind, User user)
{
    numItems++;
    Hashtable[ind].push_back(user);
}

int HashTable::hashFunction(const string& key)
{

    int hash = 0;
    for (char c : key)
    {
        hash = (hash * 31 + c) % tableSize;
    }
    return hash;
}
void HashTable::display()
{
    for (int i = 0; i < tableSize; ++i)
    {
        for (auto& item : Hashtable[i])
        {
            cout << item.GetUsername() << "," << item.GetPasssword() << "\n";
        }

    }
}
// Save hash table to a file
void HashTable::saveHashTableToFile(const string& filename)
{
	ofstream file(filename);
	if (file.is_open())
	{
		for (int i = 0; i < tableSize; ++i)
		{
			for (auto& item : Hashtable[i])
			{
				file << item.GetUsername() << "," << item.GetPasssword() << "\n";
			}
		}
		file.close();
		system("pause");
		system("cls");

	}
	else
	{
		cerr << "Error: Unable to open file " << filename << " for writing." << endl;
	}
}



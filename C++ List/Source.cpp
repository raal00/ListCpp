#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef struct ListItem 
{
	ListItem* nextItem;
	ListItem* prevItem;
	float data;
	int position;

	~ListItem()
	{
		cout << "Item " << this << " removed" << endl;
	}
}Item; 


typedef struct List 
{
	Item* top = nullptr;
	Item* bot = nullptr;

	void CreateList(string filePath) 
	{
		ifstream fin(filePath);
		int FileLines = 0;
		string Line;
		while (!fin.eof())
		{
			getline(fin, Line);
			FileLines++;
		}
		fin.close();
		fin.open(filePath);
		
		for (int i = 0; i < FileLines; i++)
		{
			Item* newItem;
			try 
			{
				newItem = new Item();
			}
			catch (bad_alloc exc) 
			{
				cout << "Exception: " << exc.what() << endl;
				break;
			}
			cout << sizeof(Item) << " bytes of memory allocated\taddress: " << newItem;

			//read all data
			fin >> newItem->data;
			newItem->position = i;
			cout << "\tData: { value: " << newItem->data << "\tposition at list: " << newItem->position << " }" << endl;


			#pragma region Linking

			newItem->prevItem = top;

			if (top != nullptr) top->nextItem = newItem; // set prev item field <nextItem> equals newItem
			newItem->nextItem = bot;

			if (bot == nullptr) bot = newItem;

			top = newItem;
			#pragma endregion

		}
		bot->prevItem = top;
		cout << "Descriptor: botAddress: " << bot << "\ttopAddress: " << top << endl;
		fin.close();
	}
	void PrintList() 
	{
		cout << "\n_____________________PRINT___________________" << endl;
		if (bot != nullptr && top != nullptr) 
		{
			cout << "*Output list from: " << bot << " to " << top << "*" << endl;
			
			Item *currentItem = bot;

			while (true) 
			{
				if (currentItem != nullptr) {
					cout << "{ " << currentItem->data << "} ";
					if (currentItem->nextItem == bot) break;
				}
				currentItem = currentItem->nextItem;
				
			}
		}
		else 
		{
			cout << "List is empty\n" << endl;
		}
		cout << "\n_____________________________________________" << endl;
	}
	void ClearList() 
	{
		cout << "\n_____________________CLEAR___________________" << endl;
		if (bot != nullptr && top != nullptr) 
		{
			Item* currentItem = bot;
			Item* next;

			while (true)
			{
				next = currentItem->nextItem;
				delete currentItem;
				if (next == bot) break;
				currentItem = next;
			}
			bot = nullptr;
			top = nullptr;
			cout << "List is clear";
		}
		else 
		{
			cout << "List is already empty";
		}
		cout << "\n_____________________________________________" << endl;
	}

	#pragma region 2 var
	Item* FindMax() 
	{
		Item* Max = bot;
		if (bot != nullptr && top != nullptr)
		{
			Item* currentItem = bot;

			while (true)
			{
				if (currentItem->data > Max->data) 
				{
					Max = currentItem;
				}
				if (currentItem->nextItem == bot) break;
				currentItem = currentItem->nextItem;
			}
			return Max;
		}
		else
		{
			cout << "List is empty\n";
		}
		return nullptr;
	}


	void DeleteFirst()
	{
		if (bot != nullptr && top != nullptr)
		{
			Item* first = bot;
			bot = bot->nextItem;
			top->nextItem = bot;
			delete first;

			Item* currentItem = bot;
			while (true)
			{
				currentItem->position--;
				if (currentItem->nextItem == bot) break;
				currentItem = currentItem->nextItem;
			}
		}
		else
		{
			cout << "List is empty\n";
		}
	}

	void InsertItem(Item* item, int position) 
	{
		bool Inserted = false;
		if (bot != nullptr && top != nullptr)
		{
			Item* currentItem = bot;
			while (true)
			{
				if (currentItem->position == position) 
				{
					item->position = position;
					item->nextItem = currentItem;
					item->prevItem = currentItem->prevItem;

					currentItem->prevItem->nextItem = item;
					currentItem->prevItem = item;
					Inserted = true;
					cout << "Item added at position " << position << endl;
				}

				if (Inserted) currentItem->position++;
				if (currentItem->nextItem == bot) break;
				currentItem = currentItem->nextItem;
			}
		}
		else
		{
			cout << "List is empty\n";
		}
	}
	#pragma endregion
}List;


int main() 
{
	setlocale(LC_ALL,  "rus");
	List list;

	// TASK 1
	list.CreateList("inputFloatValues.txt");

	// TASK 2
	list.PrintList();
	Item* max = list.FindMax();
	if (max != nullptr)
		cout << "\nMax item: " << max->data << "\nPosition at list: " << max->position << "\nAddress: " << max << endl << endl;

	// TASK 3
	list.DeleteFirst();
	list.DeleteFirst();
	list.PrintList();

	// TASK 4
	Item* newItem1 = new Item();
	Item* newItem2 = new Item();
	newItem1->data = 0.01f;
	newItem2->data = 4.4f;
	list.InsertItem(newItem1, 4);
	list.InsertItem(newItem2, 3);
	list.PrintList();

	// TASK 5
	list.ClearList();
	

	system("pause ");
	return 0;
}
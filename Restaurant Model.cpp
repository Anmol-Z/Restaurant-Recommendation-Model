//DS FINAL PROJECT
//YELP RESTAURANT DATA SET

//Group Members : 
// Anmol Zehrah - 20K0199
// Hamza Sameer Khan - 20K-1744
// Syed Abbas Ali - 20K-1630


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip> 
#include "BST.h"
#include "PQueue.h"

using namespace std;
//Restaurant Data BST
BST<vector<string>> restaurants_data;
//Priority Queue of Restaurants by location
PQ Best_Rated;
//functions
void Load_Restaurants();
void Load_Reviews();
void Load_PriorityQueue();
void Rated();
void Display_Restaurants();
void Search_Restaurants();
void Alternate_Restaurants();
void mainmenu()
{

	cout << "\n\nPress Enter to continue\n";
	cin.get();

	int check;
	system("cls");
	cout << setfill('-') << "Welcome to Main Menu" << setfill('-') << setw(10) << "\n\n\n\n";
	cout << "Enter the Command you want to perform : \n\n";
	cout << "To Load The Restaurants Data" << setfill('.') << setw(14) << "Press 1" << endl << endl;
	cout << "To Load The Reviews" << setfill('.') << setw(23) << "Press 2" << endl << endl;
	cout << "To Load Restaurants by location" << setfill('.') << setw(11) << "Press 3" << endl << endl;
	cout << "To See Best Rated Restaurants" << setfill('.') << setw(13) << "Press 4" << endl << endl;
	cout << "Display Restaurants" << setfill('.') << setw(23) << "Press 5" << endl << endl;
	cout << "Search Restaurants in our record" << setfill('.') << setw(10) << "Press 6" << endl << endl;
	cout << "Find Closest Restaurant" << setfill('.') << setw(19) << "Press 7" << endl << endl;
	cout << "Exit Main Menu" << setfill('.') << setw(28) << "Press 8" << endl << endl;
	cin >> check;
	switch (check)
	{
	case 1:
	{
		Load_Restaurants();
		break;
	}
	case 2:
	{
		Load_Reviews();
		break;
	}
	case 3:
	{
		Load_PriorityQueue();
		break;
	}
	case 4:
	{
		Rated();
		break;
	}
	case 5:
	{
		Display_Restaurants();
	    break;
	}
	case 6:
	{
		Search_Restaurants();
		break;
	}
	case 7:
	{
		Alternate_Restaurants();
		break;
	}
	case 8:
	{
		exit(0);
		break;
	}

	default:
	{
		cout << "\nWrong input entered!....Press Enter to continue\n";
		cin.get();
		mainmenu();
	}
	}


}

void Display_Restaurants()
{
	cout << "\nrestaurant Record Extracted : \n\n";
	restaurants_data.inorderTraversal();
	cin.get();
	mainmenu();

}
void Search_Restaurants()
{
	string choice;
	cout << "\nDo you want to search by Id or by name?(id/name): ";
	cin >> choice;
	cin.get();
	if (choice == "id")
	{
		cout << "\nEnter Id : ";
		getline(cin, choice);
		restaurants_data.DisplayRestaurant(choice);
	}
	else if (choice == "name")
	{
		cout << "\nEnter name : ";
		getline(cin,choice);
		restaurants_data.Displaybyname(choice);
	}
	cin.get();
	mainmenu();
}

void Alternate_Restaurants()
{
	string city, state;
	float latitude;
	float longitude;
	cout << "\nEnter your City: ";
	cin >> city;
	cout << "\nEnter your State: ";
	cin >> state;
	cout << "\nEnter Latitude and Longitude : ";
	cin >> latitude;
	cin >> longitude;
	Best_Rated.findstate(state);

	cin.get();
	mainmenu();
}


void Load_Restaurants()
{
	vector<vector<string>> business_info;
	fstream restaurants;
	restaurants.open("yelp_business.csv");
	string rows;
	string info = "";
    int read;
    cout << "Enter Number of Restaurants data you want to read(): ";
    cin >> read;
	cout << "\n\nProcessing...\n\n";
	int numofres = 0;
	for (int i = 0;  numofres<read ; i++)
	{
		vector<string> restaurant;
		getline(restaurants, rows);
		for (int j = 0; j < rows.length(); j++)
		{
			if (rows[j] == ',')
			{
				restaurant.push_back(info);
				info = "";
			}
			else if (rows[j] != '"')
			{
				info += rows[j];
			}
		}
		restaurant.push_back(info);
		info = "";
		if (restaurant.size() > 12)
		{
			if (restaurant[12].find("Restaurants") != string::npos || restaurant[12].find("Food") != string::npos)
			{
				restaurants_data.insert(restaurant);
				numofres++;
			}
		}
	}
	restaurants.close();

    cout << "Number of Restaurants Extracted : " << numofres << endl;
	cin.get();
	mainmenu();
}


void Load_Reviews()
{
    fstream rev;
	rev.open("yelp_review.csv");
	string line = "";
	string row = "";
	vector<string> reviews;
	reviews.clear();
	int count = 0;
	int read;
	cout << "\nEnter Number of Reviews you want to Load(): ";
	cin >> read;
	cout << "\n\nProcessing....\n\n";
	for (int j = 0; count < read; j++)
	{
		int i = 0;
		rev >> line;
		for (; i < line.length(); i++)
		{

			if ((line[i] == ',' && line[i + 1] == '"'))
			{
				reviews.push_back(row);
				row = "";
			}
			else if (line[i] != '"')
			{
				row += line[i];
			}

		}
		if (line[i - 1] == '"' && line[i - 2] != '"')
		{
			reviews.push_back(row);
			count++;
			restaurants_data.Check_review(reviews);
			row = "";
			reviews.clear();

		}

	}
	rev.close();
	cin.get();
	mainmenu();
}


void Load_PriorityQueue()
{
	string place;
	cout << "\n\nEnter The Location You want to compare Restaurant at(America/Europe): ";
	cin >> place;
	if (place != "America" && place != "Europe")
	{
		cout << "Wrong Input!!....Press Enter to continue";
		cin.get();
		system("cls");
		Load_PriorityQueue();
		return;
	}

	Best_Rated = restaurants_data.AddPriority(place);
	cin.get();
	mainmenu();
}

void Rated()
{
	cout << "\nWhich Option would you like to select: ";
	cout << "\n\nBest Rated Restaurant............Press 1" << endl;
	cout << "\nTop 5 Best Rated Restaurants.....Press 2" << endl;
	int n;
	cin >> n;
	if (n == 1)
	{
		string id = Best_Rated.peek();
		restaurants_data.DisplayRestaurant(id);
	}
	else if (n == 2)
	{
		string* rest = new string[5];
		Best_Rated.display(5);
		if (Best_Rated.s < 5)
		{
			cout << "\n\nInsufficient Record for Top 5\n";
		}

	}
	else
	{
		cout << "\nWrong Input!!";
	}
	cin.get();
	mainmenu();
}


int main()
 {
    mainmenu();

    return 0;
}
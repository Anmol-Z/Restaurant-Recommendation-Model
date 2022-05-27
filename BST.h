#pragma once

#include<vector>
#include<iostream>
#include<queue>
#include<string>
#include<stack>
#include "PQueue.h"
using namespace std;

template <class T>
class node
{
public:
	node<T>* left;
	node<T>* right;
	string id;
	string state;
	vector<string> RestaurantInfo;
	vector<vector<string>> reviews;
	float avg_star;
	node() : id(0), state(0), left(NULL), right(NULL)
	{}
	void calculate_star()
	{
		if (reviews.empty())
		{
			avg_star = 0;
		}
		else
		{
			int counter = 0;
			for (vector<vector<string>>::iterator i = reviews.begin(); i != reviews.end(); i++)
			{
				//string num = (*i)[3];
				string num = RestaurantInfo[9];
				avg_star += stof(num);
				counter++;
			}
			avg_star = avg_star / counter;
		}
	}
	node(vector<string> d) : RestaurantInfo(d), left(NULL), right(NULL)
	{
		id = d[0];
		state = d[5];
		reviews.clear();
		calculate_star();
	}
	void add_review(vector<string> r)
	{
		reviews.push_back(r);
		calculate_star();
	}
};

template <class T>
class BST
{
public:
	node<T>* root;
	BST() : root(NULL) {}
	void insert(T d)
	{
		node<T>* n = new node<T>(d);
		if (root == NULL)
		{
			root = n;
		}
		else
		{
			node<T>* ptr = root;
			while (ptr != NULL)
			{
				if (d[5] < ptr->state)
				{
					if (ptr->left == NULL)
					{
						ptr->left = n;
						return;
					}
					else
						ptr = ptr->left;
				}
				else
				{
					if (ptr->right == NULL)
					{
						ptr->right = n;
						return;
					}
					else
						ptr = ptr->right;
				}


			}
		}

	}

	void inorderTraversal()
	{
		stack<node<T>*> s;
		node<T>* temp = root;
		while (!s.empty() || temp != NULL)
		{
			if (temp != NULL)
			{
				s.push(temp);
				temp = temp->left;
			}
			else
			{

				temp = s.top();
				cout << endl;
				cout << "\n"<< temp->RestaurantInfo[1];
				s.pop();
				temp = temp->right;
			}
		}
	}

	void DisplayRestaurant(string id)
	{
		/*node<T>* s = search_node(id);
		if (s != NULL)
		{
			cout << endl;
			cout << "\nRestaurant Name : " << s->RestaurantInfo[1];
			cout << "\nAddress : " << s->RestaurantInfo[3];
			cout << "\nCity : " << s->RestaurantInfo[4];
			cout << "\nAverage Rating : " << s->avg_star;
		}*/
		Displaybyid(id);
	}

	node<T>* search_node(string d)
	{
		node<T>* ptr = root;
		node<T>* parent = NULL;

		while (ptr != NULL)
		{
			if (d == ptr->id)
			{
				return ptr;
			}
			else if (d < ptr->id)
			{
				parent = ptr;
				ptr = ptr->left;
			}
			else if (d > ptr->id)
			{
				parent = ptr;
				ptr = ptr->right;
			}
		}
		return ptr;

	}

	node<T>* mini(node<T>* temp)const
	{
		node<T>* ptr = temp;
		if (ptr != NULL)
		{
			while (ptr->left != 0)
			{
				ptr = ptr->left;
			}
		}
		return(ptr);
	}

	node<T>* maxi(node<T>* temp)const
	{
		node<T>* ptr = temp;
		if (ptr != NULL)
		{
			while (ptr->right != 0)
			{
				ptr = ptr->right;
			}
		}
		return(ptr);

	}
	void deletenode(string d)
	{
		root = deletenode(root, d);
	}

	node<T>* deletenode(node<T>* temp, string d)
	{

		//node<T>* temp = root;
		if (temp == NULL)
		{
			return temp;
		}
		else if (d > temp->id)
		{
			temp->right = deletenode(temp->right, d);
		}
		else if (d < temp->id)
		{
			temp->left = deletenode(temp->left, d);
		}
		else
		{
			if (temp->left == NULL && temp->right == NULL)
			{
				delete temp;
				return NULL;
			}
			else if (temp->left != NULL && temp->right == NULL)
			{
				node<T>* temp2 = temp->left;
				delete temp;
				return temp2;
			}
			else if (temp->left == NULL && temp->right != NULL)
			{
				node<T>* temp2 = temp->right;
				delete temp;
				return temp2;
			}
			else
			{
				node<T>* temp2 = mini(temp->right);
				temp->id = temp2->id;
				temp->right = deletenode(temp->right, temp2->id);
			}
		}
	}
	void Check_review(vector<string> newreview)
	{
		node<T>* check = search_node(newreview[2]);
		if (check == NULL)
		{
			return;
		}
		//cout << "\nReview added at Restaurant: " << check->RestaurantInfo[1] << " at state : " << check->RestaurantInfo[5];
		check->add_review(newreview);
	}
	bool check_state(string continent,string state)
	{
		if (continent == "America")
		{
			if (state == "C" || state == "IN" || state == "NY" || state == "AL" || state == "CA" || state == "NLK" ||
				state == "VT" || state == "AR" || state == "NI" || state == "BY" || state == "AK" || state == "FLN" || state == "FL"
				|| state == "MN" || state == "NTH" || state == "MT" || state == "GA" || state == "VA" || state == "DE" || state == "AB"
				|| state == "HU" || state == "KY" || state == "TAM" || state == "ZET" || state == "RCC" || state == "WHT" || state == "AZ"
				|| state == "PA" || state == "OH" || state == "NV" || state == "ON" || state == "NC" || state == "WI" || state == "SC"
				|| state == "QC" || state == "IL" || state == "CO" || state == "WA" || state == "NE" || state == "CMA")
			{
				return true;
			}
		}
		else if (continent == "Europe")
		{
			if(state == "HLD" || state == "WLN" || state == "ABE" || state == "SCB" || state == "KHL" || state == "ESX" || state == "NYK" 
				|| state == "FAL"||state == "ELN" || state == "PKN" || state == "ST" || state == "BW" || state == "MLN" || state == "EDH" 
				|| state == "FIF" || state == "CHE"|| state == "GLG" || state == "XGL" || state == "STG" || state == "CS" || state == "SL")
			{
				return true;
			}
		}
		return false;
	}



	PQ AddPriority(string continent)
	{
		stack<node<T>*> s;
		PQ list;
		node<T>* temp = root;
		while (!s.empty() || temp != NULL)
		{
			if (temp != NULL)
			{
				s.push(temp);
				temp = temp->left;
			}
			else
			{

				temp = s.top();
				if(check_state(continent, temp->RestaurantInfo[5]))//&&temp->avg_star!=0)
				{
					list.enqueue(temp->avg_star,temp->RestaurantInfo);
				}
				s.pop();
				temp = temp->right;
			}
		}
		return list;
	}

	void Displaybyname(string name)
	{
		stack<node<T>*> s;
		node<T>* temp = root;
		while (!s.empty() || temp != NULL)
		{
			if (temp != NULL)
			{
				s.push(temp);
				temp = temp->left;
			}
			else
			{

				temp = s.top();
				if (temp->RestaurantInfo[1] == name)
				{
					cout << endl;
					cout << "\nRestaurant Name : " << temp->RestaurantInfo[1];
					cout << "\nAddress : " << temp->RestaurantInfo[3];
					cout << "\nCity : " << temp->RestaurantInfo[4];
					//cout << "\nAverage Rating : " << temp->avg_star;
				}
				s.pop();
				temp = temp->right;
			}
		}
	}

	void Displaybyid(string name)
	{
		stack<node<T>*> s;
		node<T>* temp = root;
		while (!s.empty() || temp != NULL)
		{
			if (temp != NULL)
			{
				s.push(temp);
				temp = temp->left;
			}
			else
			{

				temp = s.top();
				if (temp->id == name)
				{
					cout << endl;
					cout << "\nRestaurant Name : " << temp->RestaurantInfo[1];
					cout << "\nAddress : " << temp->RestaurantInfo[3];
					cout << "\nCity : " << temp->RestaurantInfo[4];
					//cout << "\nAverage Rating : " << temp->avg_star;
				}
				s.pop();
				temp = temp->right;
			}
		}
	}

	~BST()
	{
		if (root != NULL)
			deletenode(root->id);
	}

};

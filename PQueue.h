#pragma once
#include<cmath>
#include<iostream>
#include<string>
#include<vector>
using namespace std;



class PNode 
{
	float data;
	string rest_id;
	string location;
	vector<string> restaurant;
	PNode* next;
public:
	PNode()
	{
		data = 0;
		rest_id = "";
		location = "";
		next = NULL;
	}
	PNode(float d, vector<string> obj)
	{
		data = d;
		rest_id = obj[0];
		location = obj[5];
		next = NULL;
		restaurant = obj;
	}
	friend class PQ;
};
class PQ 
{
public:
	PNode* front;
	PNode* back;
	int s;
	PQ()
	{
		front = NULL;
		back = NULL;
		s = 0;
	}
	PQ(const PQ &rhs)
	{
		front = rhs.front;
		back = rhs.back;
		s = rhs.s;
	}
	PQ operator=(const PQ &rhs)
	{
		front = rhs.front;
		back = rhs.back;
		s = rhs.s;
		return *this;
	}
	void enqueue(float d, vector<string> res)
	{
		s++;
		PNode* n = new PNode(d,res);
		PNode* temp = front;
		if (front == NULL)
		{
			front = n;
			back = n;
		}
		else
		{
			if(front->data < n->data)
			{
				n->next = front;
				front = n;
			}
			else {
				while (temp->next != NULL && temp->next->data > n->data)
				{
					temp = temp->next;
				}
				n->next = temp->next;
				temp->next = n;
			}
		}
	}
	float dequeue()
	{
		s--;
		if (isEmpty())
		{
			cout << "Queue is Empty" << endl;
		}
		else
		{
			PNode* todelete = front;
			float d = front->data;
			front = front->next;
			delete todelete;
			todelete = NULL;
			return d;
		}
	}
	string peek()
	{
		if (isEmpty())
		{
			cout << "Queue is Empty" << endl;
			return "";
		}
		else
		{
			return front->rest_id;
		}
	}
	bool isEmpty()
	{
		if (front == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void display()
	{
		PNode* temp = front;
		if (isEmpty())
		{
			cout << "Record is empty!" << endl;
		}
		else
		{
			while (temp != NULL)
			{
				cout << endl;
				cout << temp->location << " ";
				cout << temp->data << endl;
				temp = temp->next;
			}
			cout << endl;
		}
	}
	void display(int n)
	{
		PNode* temp = front;
		string* arr = new string[n];
		if (isEmpty())
		{
			cout << "\nRecord is empty!\n" << endl;
			return;
		}
		else
		{
			for(int i = 0 ; i < n && temp != NULL; i++)
			{
				cout << endl;
				cout << "\nRestaurant Name : " << temp->restaurant[1];
				cout << "\nAddress : " << temp->restaurant[3];
				cout << "\nCity : " << temp->restaurant[4];
				temp = temp->next;
			}
			cout << endl;
		}
	}
	void findstate(string state)
	{
		PNode* temp = front;
		cout << "\n------Nearest Best Restaurant------\n";
		while (temp != NULL)
		{
			if (temp->location == state)
			{
				cout <<"\nRestaurant Name: " << temp->restaurant[1];
				cout <<"\nAddress : " <<temp->restaurant[3];
				cout <<"\nLongitude: " << temp->restaurant[8];
				cout << "\nLatitude: " << temp->restaurant[7];
				//cout << "\nAverage Rating: " << round(temp->data);
				return;
			}
			temp = temp->next;
		}
		cout << "\nNo restaurant found near you :( \n";
	}


};
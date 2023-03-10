#include "json.hpp"
#include "person.hpp"
#include <fstream>
#include <iostream>
#include <string>

using json = nlohmann::json;

using namespace std;

// Node for our linked list
struct node {
	json data; // data value (could be a lot more values)

	node* next; // we always need a "link" in a linked list

	node(json row) { // cunstructor to make adding values easy
		data = row;
	}
};

class LinkedList {
private:
	node* head; // base pointer of list
	node* tail;

public:
	LinkedList() {
		head = tail = NULL; // NULL = zeros
		// and zeros imply empty
	}

	LinkedList(json jsonArray) {
		head = tail = NULL; // NULL = zeros
		// and zeros imply empty

		for (auto& row : jsonArray) {
			this->pushRear(row);
		}
	}

	void pushFront(json data) {
		node* tempPtr = new node(data); // create a new node and
		// add data to it

		if (!head) { // `!head` implies empty list
			// So does `head == NULL`

			head = tail = tempPtr; // `head = tempPtr` places addrress of
			// tempPtr in head (points head to tempPtr)

		}
		else {				  // list not empty
			tempPtr->next = head; // point tempPtr's next to what head points to
			head = tempPtr;		  // now point head to tempPtr
		}
	}

	void pushRear(json data) {
		node* tempPtr = new node(data); // create a new node and
		// add data to it
		if (!head) {					// `!head` implies empty list
			// So does `head == NULL`

			head = tail = tempPtr; // `head = tempPtr` places addrress of
			// tempPtr in head (points head to tempPtr)

		}
		else {
			tail->next = tempPtr; // point tempPtr's next to what head points to
			tail = tempPtr;		  // now point head to tempPtr
		}
	}

	friend ostream& operator<<(ostream& os, const LinkedList& rhs) {
		node* temp = rhs.head; // temp pointer copies head

		while (temp) { // this loops until temp is NULL
			// same as `while(temp != NULL)`

			os << temp->data; // print data from node
			if (temp->next) {
				os << "->";
			}
			temp = temp->next; // move to next node
		}
		os << endl;
		return os;
	}

	json find(string key, string value, ofstream& o) {
		int comparisons = 1;
		node* travel = head; // temp pointer copies head

		while (travel) { // this loops until temp is NULL

			if (travel->data[key] == value) {
				cout << "Record found!" << endl;
				cout << "Found after ";
				cout << comparisons << " comparisons..." << endl;
				o << "Record found!" << endl;
				o << "Found after ";
				o << comparisons << " comparisons..." << endl;
				return travel->data;
			}
			comparisons++;
			travel = travel->next; // move to next node
			
		}

		return nullptr;
	}
	
	json findInt(string key, int value, ofstream& o) {
		int comparisons = 1;
		node* travel = head; // temp pointer copies head

		while (travel) { // this loops until temp is NULL

			if (travel->data[key] == value) {
				cout << "Record found!" << endl;
				cout << "Found after ";
				cout << comparisons << " comparisons..." << endl;
				o << "Record found!" << endl;
				o << "Found after ";
				o << comparisons << " comparisons..." << endl;
				//cout << "found it";
				return travel->data;
			}

			travel = travel->next; // move to next node
			comparisons++;
		}

		return nullptr;
	}
	

	~LinkedList() {
	}
};

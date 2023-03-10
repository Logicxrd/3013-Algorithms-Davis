# /***********************************************************************
#  *
#  *  Author:           Tairique Davis
#  *  Title:            P01: Datasebase Indexes
#  *  Course:           3013 Algorithms
#  *  Semester:         Spring 2023
#  *
#  *  Description:
#           	Reads in data from a json file into AVL trees and Linked lists
#           	in order to compare time complexities. 10 deliminated fields
#	    	from the json file can be searched by modifying the program's
#	    	pre-defined searches or un-commenting the manual search code
#	    	allowing for more flexibility. Main goal of the program is to
#	    	demonstrate in real time the difference between  AVL trees'
#           	superior Olog(n) time complexity and a Linked lists O(n).
#  *        
#  *
#  ***********************************************************************/

#include <iostream>
#include <vector>
#include <fstream>
#include <cctype>
#include <string>
#include "avlTree.hpp"
#include "json.hpp"
#include "linkedList.hpp"
#include "person.hpp"
#include"timer.hpp"

using namespace std;
using json = nlohmann::json;

class TreeManager: public AvlTree {

	map <string, AvlTree*> manager;

private:

	

public:

	TreeManager(){}
	~TreeManager(){}
	void setTree(string key);
	void searchStr(string searchKey, string treeKey, ofstream& o);
	void searchInt(int searchKey, string treeKey, ofstream& o);
	void insertInt(string key, int data);
	void insertString(string key, string data);
	void printIntTree(string key);
	void printStringTree(string key);

};

//************************************************************************
// Method Name: setTree
//
// Purpose:  add tree to map of AVL Trees 
//
// Arguments: tree key 
//
// Returns:   Nothing
//*************************************************************************
void TreeManager:: setTree(string key) {
	manager[key] = new AvlTree(key);
}

//************************************************************************
// Method Name: searchStr
//
// Purpose:  uses key to find a string value from tree
//
// Arguments: key to tree type, key to node data being searched for and ofstream
//
// Returns: Nothing
//*************************************************************************
void TreeManager::searchStr(string searchKey, string treeKey, ofstream& o) {
	manager[treeKey]->searchStr(searchKey, o);
}

//************************************************************************
// Method Name: searchInt
//
// Purpose: uses key to find a int value from tree
//
// Arguments: key to tree type, key to node data being searched for and ofstream
//
// Returns: Nothing
//*************************************************************************
void TreeManager::searchInt(int searchKey, string treeKey, ofstream& o) {
		manager[treeKey]->search(searchKey, o);
	}

//************************************************************************
// Method Name: insertInt
//
// Purpose:  add int value to a tree 
//
// Arguments: key to tree type which integer where integer is being inserted
//
// Returns:   Nothing
//*************************************************************************
void TreeManager::insertInt(string key, int data) {
	manager[key]->insert(data);
}

//************************************************************************
// Method Name: insertString
//
// Purpose:  add string value to a tree 
//
// Arguments: key to tree type which integer where string is being inserted
//
// Returns:   Nothing
//*************************************************************************
void TreeManager::insertString(string key, string data) {
	manager[key]->insertStr(data);
}

//************************************************************************
// Method Name: printIntTree
//
// Purpose:  display contents of tree
//
// Arguments: key to tree type
//
// Returns:   Nothing
//*************************************************************************
void TreeManager::printIntTree(string key) {
	manager[key]->dumpTree();
}

//************************************************************************
// Method Name: printStringTree
//
// Purpose: display contents of tree
//
// Arguments:  key to tree type
//
// Returns:   Nothing
//*************************************************************************
void TreeManager::printStringTree(string key) {
	manager[key]->dumpStringTree();
}

int main() {

	Timer T;
	Timer S;
	string key;
	string data;
	int value = 0;
	
	//open input file
	//error check if file is open
	ifstream file("person_data.json");
	if (!file.is_open()) {
		cerr << "Error: could not open input file" << endl;
		return 1;
	}
	ofstream o;
	o.open("output.txt");

	json person_data = json::parse(file);

	//create Treemanager object to manage 10 Avl Trees
	TreeManager sortTree;
	sortTree.setTree("id");
	sortTree.setTree("first_name");
	sortTree.setTree("last_name");
	sortTree.setTree("email");
	sortTree.setTree("address");
	sortTree.setTree("state");
	sortTree.setTree("city");
	sortTree.setTree("car");
	sortTree.setTree("car_model");
	sortTree.setTree("car_color");

	//Parse json to linked list
	LinkedList ll(person_data);


	//loop through json file to add each data member into AVL Trees
	for (int i = 0; i < person_data.size(); ++i) {
		sortTree.insertInt("id", person_data[i]["id"]);
		sortTree.insertString("first_name", person_data[i]["first_name"]);
		sortTree.insertString("last_name", person_data[i]["last_name"]);
		sortTree.insertString("email", person_data[i]["email"]);
		sortTree.insertString("address", person_data[i]["address"]);
		sortTree.insertString("state", person_data[i]["state"]);
		sortTree.insertString("city", person_data[i]["city"]);
		sortTree.insertString("car", person_data[i]["car"]);
		sortTree.insertString("car_model", person_data[i]["car_model"]);
		sortTree.insertString("car_color", person_data[i]["car_color"]);


	}

	//GUI and pre-defined searches
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\nAccessing database..." << endl;
	cout << "This database is sorted using an Avl Tree and a Linked list";
	cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\nCommencing Search Time Test between Algorithms...";
	cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;

	//Search by IDs
	cout << "\nSearching for id '230' using AvlTree.... " << endl;
	T.Start();
	sortTree.searchInt(230, "id", o);
	T.End();
	cout << "Found in... " << T.Seconds() << " seconds.";
	cout << endl;
	o << "Found in...: " << T.Seconds() << " seconds.";
	o << endl;

	cout << "\nSearching for id '230' using Linked list.... " << endl;
	S.Start();
	json list_item = ll.findInt("id", 230, o);
	S.End();
	cout << "Found in... " << S.Seconds() << " seconds.";
	cout << endl;
	o << "Found in...: " << S.Seconds() << " seconds.";
	o << endl;
	cout << "\n";
	T.compare(T.Seconds(), S.Seconds(), o); //new method in timer hpp, compares duration between searches

	cout << "\n-------------------------------------------------------------------------------------------------------------------------" << endl;
	//Search by First Name
	cout << "\nSearching for name 'Siana' using AvlTree.... " << endl;
	T.Start();
	sortTree.searchStr("Siana", "first_name", o);
	T.End();
	cout << "Found in... " << T.Seconds() << " seconds.";
	cout << endl;
	o << "Found in...: " << T.Seconds() << " seconds.";
	o << endl;

	cout << "\nSearching for name 'Siana' using Linked List... " << endl;
	S.Start();
	json first_name_item = ll.find("first_name", "Siana", o);
	S.End();
	cout << "Found in... " << S.Seconds() << " seconds.";
	cout << endl;
	o << "Found in...: " << S.Seconds() << " seconds.";
	o << endl;
	cout << "\n";
	T.compare(T.Seconds(), S.Seconds(), o);

	cout << "\n-------------------------------------------------------------------------------------------------------------------------" << endl;
	//Search by Last Name
	cout << "\nSearching for surname 'Pantry' using AvlTree.... " << endl;
	T.Start();
	sortTree.searchStr("Pantry", "last_name", o);
	T.End();
	cout << "Found in... " << T.Seconds() << " seconds.";
	cout << endl;
	o << "Found in...: " << T.Seconds() << " seconds.";
	o << endl;

	cout << "\nSearching for surname 'Pantry' using Linked List... " << endl;
	S.Start();
	json last_name_item = ll.find("last_name", "Pantry", o);
	S.End();
	cout << "Found in... " << S.Seconds() << " seconds.";
	cout << endl;
	o << "Found in...: " << S.Seconds() << " seconds.";
	o << endl;
	cout << "\n";
	T.compare(T.Seconds(), S.Seconds(), o);

	cout << "\n-------------------------------------------------------------------------------------------------------------------------" << endl;
	//Search by email
	cout << "\nSearching for email 'fsandcroftoi@amazon.com' using AvlTree.... " << endl;
	T.Start();
	sortTree.searchStr("fsandcroftoi@amazon.com", "email", o);
	T.End();
	cout << "Found in... " << T.Seconds() << " seconds.";
	cout << endl;
	o << "Found in...: " << T.Seconds() << " seconds.";
	o << endl;

	cout << "\n\nSearching for email 'fsandcroftoi@amazon.com' using Linked List... " << endl;
	S.Start();
	json email_item = ll.find("email", "fsandcroftoi@amazon.com", o);
	S.End();
	cout << "Found in... " << S.Seconds() << " seconds.";
	cout << endl;
	o << "Found in...: " << S.Seconds() << " seconds.";
	o << endl;
	cout << "\n";
	T.compare(T.Seconds(), S.Seconds(), o);

	cout << "\n-------------------------------------------------------------------------------------------------------------------------" << endl;
	//Search by address
	cout << "\nSearching for address '2 Daystar Road' using AvlTree.... " << endl;
	T.Start();
	sortTree.searchStr("2 Daystar Road", "address", o);
	T.End();
	cout << "Found in... " << T.Seconds() << " seconds.";
	cout << endl;
	o << "Found in...: " << T.Seconds() << " seconds.";
	o << endl;

	cout << "\nSearching for address '2 Daystar Road' using Linked List... " << endl;
	S.Start();
	json address_item = ll.find("address", "2 Daystar Road", o);
	S.End();
	cout << "Found in... " << S.Seconds() << " seconds.";
	cout << endl;
	o << "Found in...: " << S.Seconds() << " seconds.";
	o << endl;
	cout << "\n";
	T.compare(T.Seconds(), S.Seconds(), o);

	cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
	//Search by state
	cout << "\nSearching for state 'New York' using AvlTree.... " << endl;
	T.Start();
	sortTree.searchStr("NY", "state", o);
	T.End();
	cout << "Found in... " << T.Seconds() << " seconds.";
	cout << endl;
	o << "Found in...: " << T.Seconds() << " seconds.";
	o << endl;

	cout << "\nSearching for state 'New York' using Linked List... " << endl;
	S.Start();
	json state_item = ll.find("state", "NY", o);
	S.End();
	cout << "Found in... " << S.Seconds() << " seconds.";
	cout << endl;
	o << "Found in...: " << S.Seconds() << " seconds.";
	o << endl;
	cout << "\n";
	T.compare(T.Seconds(), S.Seconds(), o);
	//cout << item << endl; ...display record in list

	cout << "\n-------------------------------------------------------------------------------------------------------------------------" << endl;
	//Search by city
	cout << "\nSearching for city 'Amarillo' using AvlTree.... " << endl;
	T.Start();
	sortTree.searchStr("Amarillo", "city", o);
	T.End();
	cout << "Found in... " << T.Seconds() << " seconds.";
	cout << endl;
	o << "Found in...: " << T.Seconds() << " seconds.";
	o << endl;

	cout << "\nSearching for city 'Colombus' using Linked List... " << endl;
	S.Start();
	json city_item = ll.find("city", "Amarillo", o);
	S.End();
	cout << "Found in... " << S.Seconds() << " seconds.";
	cout << endl;
	o << "Found in...: " << S.Seconds() << " seconds.";
	o << endl;
	cout << "\n";
	T.compare(T.Seconds(), S.Seconds(), o);

	cout << "\n-------------------------------------------------------------------------------------------------------------------------" << endl;
	//Search by car
	cout << "\nSearching for car 'Dodge' using AvlTree.... " << endl;
	T.Start();
	sortTree.searchStr("Dodge", "car", o);
	T.End();
	cout << "Found in... " << T.Seconds() << " seconds.";
	cout << endl;
	o << "Found in...: " << T.Seconds() << " seconds.";
	o << endl;

	cout << "\nSearching for car 'Dodge' using Linked List... " << endl;
	S.Start();
	json car_item = ll.find("car", "Dodge", o);
	S.End();
	cout << "Found in... " << S.Seconds() << " seconds.";
	cout << endl;
	o << "Found in...: " << S.Seconds() << " seconds.";
	o << endl;
	cout << "\n";
	T.compare(T.Seconds(), S.Seconds(), o);

	cout << "\n-------------------------------------------------------------------------------------------------------------------------" << endl;
	//Search by car model
	cout << "\nSearching for car model 'Cirrus' using AvlTree.... " << endl;
	T.Start();
	sortTree.searchStr("Cirrus", "car_model", o);
	T.End();
	cout << "Found in... " << T.Seconds() << " seconds.";
	cout << endl;
	o << "Found in...: " << T.Seconds() << " seconds.";
	o << endl;

	cout << "\nSearching for car model 'Cirrus' using Linked List... " << endl;
	S.Start();
	json car_model_item = ll.find("car_model", "Cirrus", o);
	S.End();
	cout << "Found in... " << S.Seconds() << " seconds.";
	cout << endl;
	o << "Found in...: " << S.Seconds() << " seconds.";
	o << endl;
	cout << "\n";
	T.compare(T.Seconds(), S.Seconds(), o);

	cout << "\n-------------------------------------------------------------------------------------------------------------------------" << endl;
	//Search by car color
	cout << "\nSearching for car color 'Red' using AvlTree.... " << endl;
	T.Start();
	sortTree.searchStr("Red", "car_color", o);
	T.End();
	cout << "Found in... " << T.Seconds() << " seconds.";
	cout << endl;
	o << "Found in...: " << T.Seconds() << " seconds.";
	o << endl;

	cout << "\nSearching for car color 'Red' using Linked List... " << endl;
	S.Start();
	json car_color_item = ll.find("car_color", "Red", o);
	S.End();
	cout << "Found in... " << S.Seconds() << " seconds.";
	cout << endl;
	o << "Found in...: " << S.Seconds() << " seconds.";
	o << endl;
	cout << "\n";
	T.compare(T.Seconds(), S.Seconds(), o);

	cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;


	/*
	//Manual Search - useful when searching other data files, this program was tested using the intial small dataset of 1000 records
	cout << "Please pick a search option from the 10 fields below:";
	cout << "\n(Items below are case sensitive, enter fields exactly as shown) ";
	cout << "\n-------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\n [id, first_name, last_name, email, address, state, city, car, car_model, car_color " << endl;
	cout << "\n-------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\nEnter field to be searched: ";
	cin >> key;

	if (key == "id")
	{

		cout << "\n\nEnter record to be searched: " << endl;
		cin >> value;
		cout << "\n\nCommencing Search...." << endl;
		cout << "\n-------------------------------------------------------------------------------------------------------------------------" << endl;
		
		cout << "\nSearching for... " << "'" << value << "' in  Avl tree by key: " << key << endl;
		T.Start();
		sortTree.searchInt(value, key, o);
		T.End();
		cout << "\nFound in... " << T.Seconds() << " seconds.";
		cout << endl;
		o << "Found in...: " << T.Seconds() << " seconds.";
		o << endl;

		cout << "\nSearching for... " << "'" << value << "' in Linked list by key: " << key << endl;
		S.Start();
		json search_item = ll.findInt(key, value, o);
		S.End();
		cout << "Found in... " << S.Seconds() << " seconds.";
		cout << endl;
		o << "Found in...: " << S.Seconds() << " seconds.";
		o << endl;
		cout << "\n-------------------------------------------------------------------------------------------------------------------------" << endl;
		T.compare(T.Seconds(), S.Seconds(), o); //new method in timer hpp, compares duration between searches
		cout << "\n-------------------------------------------------------------------------------------------------------------------------" << endl;

	}

	else {
		cout << "\n\nEnter record to be searched: " << endl;
		cin >> data;

		cout << "\n\nCommencing Search...." << endl;
		cout << "\n-------------------------------------------------------------------------------------------------------------------------" << endl;
		
		cout << "\nSearching for... " << "'" << data << "'" << " in  Avl tree by key: " << key << endl;
		T.Start();
		sortTree.searchStr(data, key, o);
		T.End();
		cout << "Found in...: " << T.Seconds() << " seconds.";
		cout << endl;
		o << "Found in...: " << T.Seconds() << " seconds.";
		o << endl;

		cout << "\nSearching for... " << "'" << data << "' in Linked list by key: " << key << endl;
		S.Start();
		json search_item = ll.find(key, data, o);
		S.End();
		cout << "Found in... " << S.Seconds() << " seconds.";
		cout << endl;
		o << "Found in...: " << S.Seconds() << " seconds.";
		o << endl;
		cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
		T.compare(T.Seconds(), S.Seconds(), o); //new method in timer hpp, compares duration between searches
		cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
	}


	
	*/

	 file.close(); //close file

}

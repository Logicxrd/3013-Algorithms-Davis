#pragma once

#include "json.hpp"
#include <iostream>
#include <string>

using json = nlohmann::json;

using namespace std;

// id,first_name,last_name,email,gender,salary
struct Person {
	int id;
	string first_name;
	string last_name;
	string email;
	string address;
	string state;
	string city;
	string car;
	string car_model;
	string car_color;

	Person() {
		// default constructor
	}

	// comma delimited row
	Person(json row) {
		this->first_name = row["first_name"];
		this->last_name = row["last_name"];
		this->email = row["email"];
		this->address = row["address"];
		this->state = row["state"];
		this->city = row["city"];
		this->car = row["car"];
		this->car_model = row["car_model"];
		this->car_color = row["car_color"];
	}

	friend ostream& operator<<(ostream& os, const Person& rhs) {
		os << "[" << rhs.first_name << " " << rhs.last_name << " " << rhs.email
			<< " " << rhs.address << " " << rhs.state << " " << rhs.city << " " << rhs.car << " " << rhs.car_model << " " << rhs.car_color
			<< "] ";
		return os;
	}
};

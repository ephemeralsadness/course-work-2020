#pragma once
#include<string>
#include "Vector.h"

class Company {
public:

	Company() :name("Empty"),
		services(),
		adress("Empty") {}

	Company(std::string n, Vector<std::string> s, std::string a) {
		name = n;
		services = s;
		adress = a;
	}

	std::string GetName() const;
	Vector<std::string> GetServices() const;
	std::string GetAdress() const;

	void SetName(std::string n);
	void SetServices(Vector<std::string> s);
	void SetAdress(std::string a);

public:
	std::string name;
	Vector<std::string> services;
	std::string adress;
};


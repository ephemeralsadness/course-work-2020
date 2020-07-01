#pragma once
#include<string>
#include "../helper/Vector.h"

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
	Vector<std::string>& GetServices();
	const Vector<std::string>& Company::GetServices() const;
	std::string GetAdress() const;

	void SetName(std::string n);
	void SetAdress(std::string a);

public:
	std::string name;
	Vector<std::string> services;
	std::string adress;
};


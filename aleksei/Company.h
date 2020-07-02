#pragma once

#include <utility>
#include <string>
#include "../helper/Vector.h"

class Company {
public:

	Company() : name("Empty"),
                services(),
                address("Empty") {}

	Company(std::string n, Vector<std::string> s, std::string a)
            : name(std::move(n)),
              services(std::move(s)),
              address(std::move(a)) {
		name = n;
		services = s;
        address = a;
	}

	std::string GetName() const;
	Vector<std::string>& GetServices();
	const Vector<std::string>& GetServices() const;
	std::string GetAddress() const;

	void SetName(std::string n);
	void SetAddress(std::string a);

public:
	std::string name;
	Vector<std::string> services;
	std::string address;
};


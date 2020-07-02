#pragma once

#include <utility>
#include <string>
#include "../helper/Vector.h"

class Company {
public:

	Company() : name("Empty"),
                services(),
                address("Empty") {}

	Company(std::string name, Vector<std::string> services, std::string address)
            : name(std::move(name)),
              services(std::move(services)),
              address(std::move(address)) {
	}

    const std::string& GetName() const;
	Vector<std::string>& GetServices();
	const Vector<std::string>& GetServices() const;
    const std::string& GetAddress() const;

	void SetName(std::string n);
	void SetAddress(std::string a);

public:
	std::string name;
	Vector<std::string> services;
	std::string address;
};


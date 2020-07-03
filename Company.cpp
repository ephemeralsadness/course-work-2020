#include "Company.h"

const std::string& Company::GetName() const {
	return name;
}

Vector<std::string>& Company::GetServices() {
	return services;
}

const Vector<std::string>& Company::GetServices() const {
	return services;
}


const std::string& Company::GetAddress() const {
	return address;
}

void Company::SetName(std::string n) {
	name = std::move(n);
}

void Company::SetAddress(std::string a) {
    address = std::move(a);
}

#include "Company.h"

std::string Company::GetName() const {
	return name;
}

Vector<std::string>& Company::GetServices() {
	return services;
}

const Vector<std::string>& Company::GetServices() const {
	return services;
}


std::string Company::GetAdress() const {
	return adress;
}

void Company::SetName(std::string n) {
	name = n;
}

void Company::SetAdress(std::string a) {
	adress = a;
}

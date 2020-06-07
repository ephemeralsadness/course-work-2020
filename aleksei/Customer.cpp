#include"Customer.h"

std::string Customer::GetName() const{
	return name;
}

std::string Customer::GetService() const {
	return service;
}

std::string Customer::GetCompanyName() const {
	return company_name;
}

uint16_t Customer::GetVolume() const {
	return volume;
}

void Customer::SetName(std::string s) {
	name = s;
}

void Customer::SetService(std::string s) {
	service = s;
}

void Customer::SetCompanyName(std::string s) {
	company_name = s;
}

void Customer::SetVolume(uint16_t v) {
	volume = v;
}
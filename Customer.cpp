#include "Customer.h"

const std::string& Customer::GetName() const{
	return name;
}

const std::string& Customer::GetService() const {
	return service;
}

const std::string& Customer::GetCompanyName() const {
	return company_name;
}

uint16_t Customer::GetVolume() const {
	return volume;
}

void Customer::SetName(std::string s) {
	name = std::move(s);
}

void Customer::SetService(std::string s) {
	service = std::move(s);
}

void Customer::SetCompanyName(std::string s) {
	company_name = std::move(s);
}

void Customer::SetVolume(uint16_t v) {
	volume = v;
}
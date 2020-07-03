#pragma once

#include<string>
#include "Vector.h"

class Customer {
public:

	Customer() : name("Empty"),
				 service("Empty"),
				 company_name("Empty"),
				 volume(0) {}

	Customer(std::string name, std::string service, std::string company, uint16_t volume)
		:   name(std::move(name)),
		    service(std::move(service)),
		    company_name(std::move(company)),
		    volume(volume) {}
				
	const std::string& GetName() const;
    const std::string& GetService() const;
    const std::string& GetCompanyName() const;
	uint16_t GetVolume() const;

	void SetName(std::string s);
	void SetService(std::string s);
	void SetCompanyName(std::string s);
	void SetVolume(uint16_t v);

private:
	std::string name;
	std::string service;
	std::string company_name;
	uint16_t volume;
};

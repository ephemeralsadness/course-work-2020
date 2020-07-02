#pragma once

#include<string>
#include "../helper/Vector.h"

class Customer {
public:

	Customer() : name("Empty"),
				 service("Empty"),
				 company_name("Empty"),
				 volume(0) {}

	Customer(std::string n, std::string s, std::string c, uint16_t v)
		:   name(std::move(n)),
		    service(std::move(s)),
		    company_name(std::move(c)),
		    volume(v) {}
				
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

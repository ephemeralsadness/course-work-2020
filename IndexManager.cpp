#include "IndexManager.h"
#include "BinarySearchTree.h"

#include <stdexcept>
#include <fstream>

void IndexManager::AddCompany(std::string company_name, std::string address) {
    Company c = Company(std::move(company_name), {}, std::move(address));

	bool success = _companies.Insert(std::move(c));

	if (!success) {
		throw std::invalid_argument("Компания с таким названием уже есть в базе данных");
	}
}

void IndexManager::AddCustomer(std::string name, std::string service, std::string company, uint16_t volume) {
	Customer c(std::move(name), std::move(service), std::move(company), volume);
	const Company* c_ptr = _companies.Find(c.GetCompanyName());

	if (c_ptr == nullptr) {
		throw std::invalid_argument("Компании с таким названием нету в базе данных");
	}

	bool has_service = false;
	for (auto it = c_ptr->GetServices().Begin(); it != c_ptr->GetServices().End(); ++it) {
		if (*it == c.GetService()) {
			has_service = true;
			break;
		}
	}

	if (has_service) {
		_customers.Insert(std::move(c));
	} else {
		throw std::invalid_argument("Данная компания не предоставляет такой услуги");
	}

}


void IndexManager::AddServicePrice(std::string name, std::string company, double price, std::string measure) {
	ServicePrice sp(std::move(name), std::move(company), price, std::move(measure));

    auto ptr = _service_durations.Find(sp.GetName());
    if (ptr == nullptr) {
        throw std::invalid_argument("Данной услуги нету в базе данных");
    }

	auto lambda = [&sp](const ServicePrice& s) {
		return s.GetCompany() == sp.GetCompany();
	};
	auto v = _service_prices.Find(sp.GetName(), lambda);

	if (v.Size() != 0) {
		throw std::invalid_argument("Услуга уже предоставляется данной компанией");
	}

	bool success = _companies.InsertService(sp.GetCompany(), sp.GetName());
	if (!success) {
		throw std::invalid_argument("Компании с таким названием нету в базе данных");
	}

	_service_prices.Insert(std::move(sp));
}


void IndexManager::AddServiceDuration(std::string name, double min_duration, double max_duration) {
	ServiceDuration sd(std::move(name), min_duration, max_duration);

	bool success = _service_durations.Insert(std::move(sd));
	if (!success) {
		throw std::invalid_argument("Данная услуга уже существует");
	}
}

void IndexManager::RemoveCompany(const std::string &name) {
	bool success = _companies.Remove(name);
	if (!success) {
		throw std::invalid_argument("Компании с таким названием нету в базе данных");
	}

	auto customer_lambda = [&name](const Customer& c) {
		return c.GetCompanyName() == name;
	};
	_customers.Remove(customer_lambda);

	auto service_price_lambda = [&name](const ServicePrice& sp) {
		return sp.GetCompany() == name;
	};
	_service_prices.Remove(service_price_lambda);

}

void IndexManager::RemoveCustomer(const std::string &name) {
	auto v = _customers.Find(name);

	if (v.Size() == 0) {
		throw std::invalid_argument("Клиента с таким именем нету в базе данных");
	}

	_customers.Remove(name);
}

void IndexManager::RemoveServicePrice(const std::string &name, const std::string& company) {
	auto lambda = [&company](const ServicePrice& sp) {
		return company == sp.GetCompany();
	};
	auto v = _service_prices.Find(name, lambda);

	if (v.Size() == 0) {
		throw std::invalid_argument("Данная компания не предоставляет такой услуги");
	}

	_service_prices.Remove(name, lambda);

	_companies.RemoveService(company, name);

	auto customer_lambda = [&name, &company](const Customer& c) {
		return name == c.GetService() && company == c.GetCompanyName();
	};
	_customers.Remove(customer_lambda);
}

void IndexManager::RemoveServiceDuration(const std::string &name) {
	bool success = _service_durations.Remove(name);

	if (!success) {
		throw std::invalid_argument("Данной услуги нету в базе данных");
	}

	auto& companies_field = _companies;
	auto lambda = [&name, &companies_field](const ServicePrice& sp) {
        companies_field.RemoveService(sp.GetCompany(), name);
		return true;
	};
	_service_prices.Remove(name, lambda);

	auto customer_lambda = [&name](const Customer& c) {
		return name == c.GetService();
	};
    _customers.Remove(customer_lambda);
}

Company IndexManager::FindCompany(const std::string &name) {
	auto company_ptr = _companies.Find(name);
	_last_comparisons_amount = _companies.LastComparisonsAmount();

	if (company_ptr == nullptr) {
		throw std::invalid_argument("Компании с таким названием нету в базе данных");
	}
	return *company_ptr;
}

Vector<Customer> IndexManager::FindCustomer(const std::string &name) {
	Vector<Customer> result;

	auto customer_ptrs = _customers.Find(name);
	_last_comparisons_amount = _customers.LastComparisonsAmount();

	if (customer_ptrs.Size() == 0) {
		throw std::invalid_argument("Заказчика с таким именем нету в базе данных");
	}

	for (auto it = customer_ptrs.Begin(); it != customer_ptrs.End(); ++it)
		result.PushBack(**it);

	return result;
}


Vector<ServicePrice> IndexManager::FindServicePrice(const std::string &name) {
	Vector<ServicePrice> result;
	auto service_price_ptrs = _service_prices.Find(name);
	_last_comparisons_amount = _service_prices.LastComparisonsAmount();

	if (service_price_ptrs.Size() == 0) {
		throw std::invalid_argument("Компаний, выполняющих данную услугу нету в базе данных");
	}

	for (auto it = service_price_ptrs.Begin(); it != service_price_ptrs.End(); ++it)
		result.PushBack(**it);

	return result;
}


ServiceDuration IndexManager::FindServiceDuration(const std::string &name) {
	auto service_duration_ptr = _service_durations.Find(name);
	_last_comparisons_amount = _service_durations.LastComparisonsAmount();

	if (service_duration_ptr == nullptr) {
		throw std::invalid_argument("Компании с таким названием нету в базе данных");
	}
	return *service_duration_ptr;
}

Vector<Pair<Company, size_t>> IndexManager::LookUpCompanies() {
	Vector<Pair<Company, size_t>> result;
	auto v = _companies.LookUp();
	for (auto it = v.Begin(); it != v.End(); ++it) {
		result.PushBack({*it->first, it->second});
	}

	return result;
}

Vector<Customer> IndexManager::LookUpCustomers() {
	Vector<Customer> result;
	auto v = _customers.LookUp();
	for (auto it = v.Begin(); it != v.End(); ++it) {
		result.PushBack(**it);
	}

	return result;
}
Vector<ServicePrice> IndexManager::LookUpServicePrices() {
	Vector<ServicePrice> result;
	auto v = _service_prices.LookUp();
	for (auto it = v.Begin(); it != v.End(); ++it) {
		result.PushBack(**it);
	}

	return result;
}
Vector<Pair<ServiceDuration, size_t>> IndexManager::LookUpServiceDurations() {
	Vector<Pair<ServiceDuration, size_t>> result;
	auto v = _service_durations.LookUp();
	for (auto it = v.Begin(); it != v.End(); ++it) {
		result.PushBack({*it->first, it->second});
	}

	return result;
}

void IndexManager::SaveData(const std::string &file_name) {
	std::ofstream fout(file_name);

	auto company_lookup = _companies.LookUp();
	auto customer_lookup = _customers.LookUp();
	auto service_price_lookup = _service_prices.LookUp();
	auto service_duration_lookup = _service_durations.LookUp();

	fout << company_lookup.Size() << '\n';
	for (auto it = company_lookup.Begin(); it != company_lookup.End(); ++it) {
		const Company& c = *it->first;
		fout << c.GetName() << '\n';

		auto& v = c.GetServices();
		fout << v.Size() << '\n';
		for (auto jt = v.Begin(); jt != v.End(); ++jt) {
			fout << *jt << '\n';
		}

		fout << c.GetAddress() << '\n';
	}

	fout << customer_lookup.Size() << '\n';
	for (auto it = customer_lookup.Begin(); it != customer_lookup.End(); ++it) {
		const Customer& c = **it;
		fout << c.GetName() << '\n';
		fout << c.GetService() << '\n';
		fout << c.GetCompanyName() << '\n';
		fout << c.GetVolume() << '\n';
	}

	fout << service_price_lookup.Size() << '\n';
	for (auto it = service_price_lookup.Begin(); it != service_price_lookup.End(); ++it) {
		const ServicePrice& sp = **it;
		fout << sp.GetName() << '\n';
		fout << sp.GetCompany() << '\n';
		fout << sp.GetPrice() << '\n';
		fout << sp.GetMeasure() << '\n';
	}

	fout << service_duration_lookup.Size() << '\n';
	for (auto it = service_duration_lookup.Begin(); it != service_duration_lookup.End(); ++it) {
		const ServiceDuration& sd = *it->first;
		fout << sd.GetName() << '\n';
		fout << sd.GetMinDuration() << '\n';
		fout << sd.GetMaxDuration() << '\n';
	}


}

void IndexManager::LoadData(const std::string &file_name) {
	std::ifstream fin(file_name);
	std::string buffer;

	{
		std::getline(fin, buffer);
		size_t amount = std::stoull(buffer);

		for (size_t i = 0; i < amount; ++i) {
			std::string name;
			std::getline(fin, name);

			Vector<std::string> services;
			std::getline(fin, buffer);

			size_t services_amount = std::stoull(buffer);
			for (size_t j = 0; j < services_amount; ++j) {
				std::getline(fin, buffer);
				services.PushBack(buffer);
			}

			std::string address;
			std::getline(fin, address);

			_companies.Insert(Company(std::move(name), std::move(services), std::move(address)));
		}
	}

	{
		std::getline(fin, buffer);
		size_t amount = std::stoull(buffer);

		for (size_t i = 0; i < amount; ++i) {
			std::string name;
			std::getline(fin, name);

			std::string service;
			std::getline(fin, service);

			std::string company_name;
			std::getline(fin, company_name);

			std::getline(fin, buffer);
			int16_t volume = std::stoi(buffer);

			_customers.Insert(Customer(std::move(name), std::move(service), std::move(company_name), volume));
		}
	}

	{
		std::getline(fin, buffer);
		size_t amount = std::stoull(buffer);

		for (size_t i = 0; i < amount; ++i) {
			std::string name;
			std::getline(fin, name);

			std::string company;
			std::getline(fin, company);

			std::getline(fin, buffer);
			double price = std::stod(buffer);

			std::string measure;
			std::getline(fin, measure);

			_service_prices.Insert(ServicePrice(std::move(name), std::move(company), price, std::move(measure)));
		}
	}

	{
		std::getline(fin, buffer);
		size_t amount = std::stoull(buffer);

		for (size_t i = 0; i < amount; ++i) {
			std::string name;
			std::getline(fin, name);

			std::getline(fin, buffer);
			double min_duration = std::stod(buffer);

			std::getline(fin, buffer);
			double max_duration = std::stod(buffer);

			_service_durations.Insert(ServiceDuration(std::move(name), min_duration, max_duration));
		}
	}

}

// vector of {company name, income of this company}
Vector<Pair<std::string, double>> IndexManager::GetCompaniesIncomes() {
    BinarySearchTree<std::string, double> tree;

    auto customers = _customers.LookUp();
    for (auto it = customers.Begin(); it != customers.End(); ++it) {
        auto lambda = [it](const ServicePrice& sp) {
            return sp.GetCompany() == (**it).GetCompanyName();
        };
        auto v = _service_prices.Find((**it).GetService(), lambda);

        auto ptr = tree.Find((**it).GetCompanyName());
        double value = v[0]->GetPrice() * (**it).GetVolume();
        if (ptr == nullptr) {
            tree.Insert((**it).GetCompanyName(), value);
        } else {
            *ptr += value;
        }
    }

    Vector<Pair<std::string, double>> result;
    tree.ForEach([&result](const std::string& key, double value){
        result.PushBack({key, value});
    });

	return result;
}

// vector of {company name, vector of its clients}
Vector<Pair<std::string, Vector<std::string>>> IndexManager::GetCompaniesClients() {
    BinarySearchTree<std::string, Vector<std::string>> tree;
    auto lookup = _customers.LookUp();

    for (auto it = lookup.Begin(); it != lookup.End(); ++it) {
        auto ptr = tree.Find((**it).GetCompanyName());
        if (ptr == nullptr) {
            Vector<std::string> to_insert; to_insert.PushBack((**it).GetName());
            tree.Insert((**it).GetCompanyName(), std::move(to_insert));
        } else {
            ptr->PushBack((**it).GetName());
        }
    }

    Vector<Pair<std::string, Vector<std::string>>> result;
    tree.ForEach([&result](const std::string& key, const Vector<std::string>& value){
        result.PushBack({key, value});
    });

    return result;
}


// vector of {customer name, {min duration of its services, max duration of its services}}
Vector<Pair<std::string, Pair<double, double>>> IndexManager::GetCustomersServiceDurations() {
	Vector<Pair<std::string, Pair<double, double>>> result;
	auto lookup = _customers.LookUp();

	std::string current_customer;
	for (auto it = lookup.Begin(); it != lookup.End(); ++it) {
		const ServiceDuration* sd = _service_durations.Find((**it).GetService());
		if ((**it).GetName() != current_customer) {
			current_customer = (**it).GetName();
			result.PushBack({current_customer, {0, 0}});
		}
		result[result.Size() - 1].second.first += sd->GetMinDuration() * (**it).GetVolume();
		result[result.Size() - 1].second.second += sd->GetMaxDuration() * (**it).GetVolume();
	}

	return result;
}

// vector of {service, {companies, who perform this service}}
Vector<Pair<std::string, Vector<std::string>>> IndexManager::GetServiceCompanies() {
    BinarySearchTree<std::string, Vector<std::string>> tree;

    auto companies = _companies.LookUp();
    for (auto it = companies.Begin(); it != companies.End(); ++it) {
        auto v = it->first->GetServices();
        for (auto jt = v.Begin(); jt != v.End(); ++jt) {
            auto ptr = tree.Find(*jt);
            if (ptr == nullptr) {
                Vector<std::string> to_insert; to_insert.PushBack(it->first->GetName());
                tree.Insert(*jt, std::move(to_insert));
            } else {
                ptr->PushBack(it->first->GetName());
            }
        }
    }

    Vector<Pair<std::string, Vector<std::string>>> result;
    tree.ForEach([&result](const std::string& key, const Vector<std::string>& value){
        result.PushBack({key, value});
    });

    return result;
}


size_t IndexManager::GetLastComparisonsAmount() {
	return _last_comparisons_amount;
}

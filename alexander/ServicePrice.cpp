#include "ServicePrice.h"

ServicePrice::name_t ServicePrice::GetName() {
    return _name;
}

ServicePrice::company_t ServicePrice::GetCompany() {
    return _company;
};

ServicePrice::price_t ServicePrice::GetPrice() {
    return _price;
}

ServicePrice::measure_t ServicePrice::GetMeasure() {
    return _measure;
}

void ServicePrice::SetName(ServicePrice::name_t name) {
    _name = std::move(name);
}

void ServicePrice::SetCompany(ServicePrice::company_t company) {
    _company = std::move(company);
}

void ServicePrice::SetPrice(ServicePrice::price_t price) {
    _name = std::move(price);
}

void ServicePrice::SetMeasure(ServicePrice::measure_t measure) {
    _company = std::move(measure);
}

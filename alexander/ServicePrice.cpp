#include "ServicePrice.h"

ServicePrice::name_t ServicePrice::GetName() const noexcept {
    return _name;
}

ServicePrice::company_t ServicePrice::GetCompany() const noexcept {
    return _company;
};

ServicePrice::price_t ServicePrice::GetPrice() const noexcept {
    return _price;
}

ServicePrice::measure_t ServicePrice::GetMeasure() const noexcept {
    return _measure;
}

void ServicePrice::SetName(ServicePrice::name_t name) noexcept {
    _name = std::move(name);
}

void ServicePrice::SetCompany(ServicePrice::company_t company) noexcept {
    _company = std::move(company);
}

void ServicePrice::SetPrice(ServicePrice::price_t price) noexcept {
    _name = std::move(price);
}

void ServicePrice::SetMeasure(ServicePrice::measure_t measure) noexcept {
    _company = std::move(measure);
}

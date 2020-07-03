#include "ServiceDuration.h"

ServiceDuration::name_t ServiceDuration::GetName() const noexcept {
    return _name;
}

ServiceDuration::duration_t ServiceDuration::GetMinDuration() const noexcept {
    return _min_duration;
}

ServiceDuration::duration_t ServiceDuration::GetMaxDuration() const noexcept {
    return _max_duration;
}

void ServiceDuration::SetName(name_t name) noexcept {
    _name = std::move(name);
}

void ServiceDuration::SetMinDuration(duration_t min_duration) noexcept {
    _min_duration = min_duration;
}

void ServiceDuration::SetMaxDuration(duration_t max_duration) noexcept {
    _max_duration = max_duration;
}
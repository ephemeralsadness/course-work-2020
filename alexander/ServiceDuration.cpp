#include "ServiceDuration.h"

ServiceDuration::name_t ServiceDuration::GetName() {
    return _name;
}

ServiceDuration::duration_t ServiceDuration::GetMinDuration() {
    return _min_duration;
}

ServiceDuration::duration_t ServiceDuration::GetMaxDuration() {
    return _max_duration;
}

void ServiceDuration::SetName(name_t name) {
    _name = std::move(name);
}

void ServiceDuration::SetMinDuration(duration_t min_duration) {
    _min_duration = std::move(min_duration);
}

void ServiceDuration::SetMaxDuration(duration_t max_duration) {
    _max_duration = std::move(max_duration);
}
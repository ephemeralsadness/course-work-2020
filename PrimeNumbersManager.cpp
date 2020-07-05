#include "PrimeNumbersManager.h"

size_t PrimeNumbersManager::Get() {
	return _prime_numbers[_index];
}

PrimeNumbersManager& PrimeNumbersManager::Next() {
	if (_index < _size)
		++_index;
	return *this;
}
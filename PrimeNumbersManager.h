#pragma once

#include <cstddef>

class PrimeNumbersManager {
public:
    size_t Get();
    PrimeNumbersManager& Next();
private:
    size_t _index = 0;
    constexpr static size_t _size = 50;
    constexpr static size_t
        _prime_numbers[_size] = { 2U, 5U, 11U, 17U, 29U, 47U, 71U, 107U, 163U,
                                 251U, 379U, 569U, 857U, 1289U, 1949U, 2927U,
                                 4391U, 6599U, 9901U, 14867U, 22303U, 33457U,
                                 50207U, 75323U, 112997U, 169501U, 254257U,
                                 381389U, 572087U, 858149U, 1287233U, 1930879U,
                                 2896319U, 4344479U, 6516739U, 9775111U, 14662727U,
                                 21994111U, 32991187U};
};

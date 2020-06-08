#pragma once

#include <cstddef>

class PrimeNumbersManager {
public:
    size_t Get();
    PrimeNumbersManager& Next();
private:
    size_t _index = 0;
    constexpr static size_t _size = 49;
    constexpr static size_t
            _prime_numbers[_size] = { 2, 5, 11, 17, 29, 47, 71, 107, 163, 251, 379,
                                      569, 857, 1289, 1949, 2927, 4391, 6599, 9901,
                                      14867, 22303, 33457, 50207, 75323, 112997,
                                      169501, 254257, 381389, 572087, 858149, 1287233,
                                      1930879, 2896319, 4344479, 6516739, 9775111,
                                      14662727, 21994111, 32991187, 49486793, 74230231,
                                      111345347, 167018021, 250527047, 375790601,
                                      563685907, 845528867, 1268293309, 1902439967 };
};
#pragma once

#include <cstddef>

class PrimeNumbersManager {
public:
    size_t Get();
    PrimeNumbersManager& Next();
private:
    size_t _index = 0;
    constexpr static size_t _size = 75;
    constexpr static size_t
            _prime_numbers[_size] = {2UL, 5UL, 11UL, 17UL, 29UL, 47UL, 71UL, 107UL, 163UL,
                                     251UL, 379UL, 569UL, 857UL, 1289UL, 1949UL, 2927UL,
                                     4391UL, 6599UL, 9901UL, 14867UL, 22303UL, 33457UL,
                                     50207UL, 75323UL, 112997UL, 169501UL, 254257UL,
                                     381389UL, 572087UL, 858149UL, 1287233UL, 1930879UL,
                                     2896319UL, 4344479UL, 6516739UL, 9775111UL, 14662727UL,
                                     21994111UL, 32991187UL, 49486793UL, 74230231UL,
                                     111345347UL, 167018021UL, 250527047UL, 375790601UL,
                                     563685907UL, 845528867UL, 1268293309UL, 1902439967UL,
                                     2853659981UL, 4280489981UL, 6420734989UL, 9631102487UL,
                                     14446653731UL, 21669980653UL, 32504971021UL, 48757456567UL,
                                     73136184871UL, 109704277337UL, 164556416029UL, 246834624053UL,
                                     370251936113UL, 555377904197UL, 833066856311UL,
                                     1249600284509UL, 1874400426809UL, 2811600640271UL,
                                     4217400960467UL, 6326101440707UL, 9489152161087UL,
                                     14233728241643UL, 21350592362537UL, 32025888543809UL,
                                     48038832815767UL, 72058249223771UL};
};
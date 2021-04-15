#pragma once


#include <cstddef>
#include <cstdint>

#include <ctime>
#include <random>

#include <cppitertools/itertools.hpp>


namespace utils {

template <int numSides>
class Die {
public:
	int roll() {
		return dist(getRandom);
	}

	int getMax() const {
		return numSides;
	}

	double getAverage() const {
		return 1 + (getMax() - 1) / 2.0;
	}

private:
	inline static std::default_random_engine getRandom{(unsigned)time(nullptr)};

	std::uniform_int_distribution<int> dist{1, numSides};
};


namespace dice {

using d4_t   = Die<4>;
using d6_t   = Die<6>;
using d8_t   = Die<8>;
using d10_t  = Die<10>;
using d12_t  = Die<12>;
using d20_t  = Die<20>;
using d100_t = Die<100>;

inline d4_t   d4;
inline d6_t   d6;
inline d8_t   d8;
inline d10_t  d10;
inline d12_t  d12;
inline d20_t  d20;
inline d100_t d100;

}

}

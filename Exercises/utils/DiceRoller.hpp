#pragma once


#include <cstddef>
#include <cstdint>

#include <utils/Die.hpp>

#include <cppitertools/range.hpp>


namespace utils {

template <typename DieType>
class DiceRoller {
public:
	DiceRoller(int numDice, const DieType& die)
	: numDice_(numDice),
	  die_(die) { }

	int roll() {
		int result = 0;
		for ([[maybe_unused]] int i : iter::range(numDice_))
			result += die_.roll();
		return result;
	}

	double getAverage() const {
		return numDice_ * die_.getAverage();
	}

	friend DiceRoller operator*(int multiplier, const DiceRoller& roller) {
		return {multiplier * roller.numDice_, roller.die_};
	}

	friend DiceRoller operator*(const DiceRoller& roller, int multiplier) {
		return {multiplier * roller.numDice_, roller.die_};
	}

private:
	int numDice_;
	DieType die_;
};


template <int numSides>
DiceRoller<Die<numSides>> operator*(int numDice, const Die<numSides>& die) {
	return {numDice, die};
}

}

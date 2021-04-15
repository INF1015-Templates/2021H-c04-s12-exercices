#include <cstddef>
#include <cstdint>

#include <cmath>
#include <utility>

#include <QString>

#include "Ability.hpp"


namespace stats {

Ability::Ability(AbilityId id, int score)
: id_(id),
  score_(score) { }

AbilityId Ability::getId() const {
	return id_;
}

int Ability::getScore() const {
	return score_;
}

void Ability::setScore(int score) {
	score_ = score;
}

int Ability::getModifier() const {
	return (int)floor((getScore() - 10) / 2.0);
}

}


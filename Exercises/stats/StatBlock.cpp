#include <cstddef>
#include <cstdint>

#include <cmath>
#include <utility>

#include <QString>

#include "StatBlock.hpp"


namespace stats {

const Ability& StatBlock::getAbility(AbilityId id) const {
	return abilities_[id];
}

Ability& StatBlock::getAbility(AbilityId id) {
	return abilities_[id];
}

int StatBlock::getArmorClass() const {
	return armorClass_;
}

void StatBlock::setArmorClass(int ac) {
	armorClass_ = ac;
}

int StatBlock::getMaxHp() const {
	return maxHp_;
}

void StatBlock::setMaxHp(int hp) {
	maxHp_ = hp;
	setCurrentHp(getCurrentHp());
}

int StatBlock::getCurrentHp() const {
	return currentHp_;
}

void StatBlock::setCurrentHp(int hp) {
	currentHp_ = std::clamp(hp, 0, maxHp_);
}

int StatBlock::getTemporaryHp() const {
	return tempHp_;
}

void StatBlock::setTemporaryHp(int hp) {
	tempHp_ = hp;
}

}


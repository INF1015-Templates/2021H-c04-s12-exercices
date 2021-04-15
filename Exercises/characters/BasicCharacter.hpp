#pragma once


#include <cstddef>
#include <cstdint>

#include <utility>
#include <span>
#include <cmath>
#include <unordered_set>

#include <QString>

#include <utils/Die.hpp>
#include <characters/AbstractCharacter.hpp>


namespace characters {

template <typename HitDiceType>
class BasicCharacter : public virtual AbstractCharacter {
public:
	BasicCharacter(const QString& name, std::span<stats::Ability, stats::numAbilities> abilities);
	
	const QString& getName() const override;
	int getLevel() const override;
	int getProficiencyBonus() const override;
	void levelUp(bool useAverageHitDie) override;
	void takeDamage(int damage) override;
	bool hasSaveProficiency(stats::AbilityId ability) const override;
	void addSaveProficiency(stats::AbilityId ability) override;
	void removeSaveProficiency(stats::AbilityId ability) override;
	int rollInitiative() override;
	int rollSavingThrow(stats::AbilityId ability) override;
	int getNumAttacksPerAction() const override;
	std::tuple<int, int, bool> rollUnarmedAttack() override;
	int rollUnarmedDamage(bool crit) override;

private:
	QString name_;
	int level_ = 1;
	HitDiceType hitDie_;
	std::unordered_set<stats::AbilityId> saveProficiencies_;
};


template <typename HitDiceType>
BasicCharacter<HitDiceType>::BasicCharacter(const QString& name, std::span<stats::Ability, stats::numAbilities> abilities)
: name_(name) {
	for (auto&& ab : abilities)
		getAbility(ab.getId()) = ab;
	setMaxHp(hitDie_.getMax() + getConstitutionModifier());
	setCurrentHp(getMaxHp());
	setArmorClass(10 + getDexterityModifier());
}

template <typename HitDiceType>
const QString& BasicCharacter<HitDiceType>::getName() const {
	return name_;
}

template <typename HitDiceType>
int BasicCharacter<HitDiceType>::getLevel() const {
	return level_;
}

template <typename HitDiceType>
int BasicCharacter<HitDiceType>::getProficiencyBonus() const {
	return (getLevel() - 1) / 4 + 2;
}

template <typename HitDiceType>
void BasicCharacter<HitDiceType>::levelUp(bool useAverageHitDie) {
	int hitDieRoll = useAverageHitDie ? (int)ceil(hitDie_.getAverage()) : hitDie_.roll();
	setMaxHp(getMaxHp() + hitDieRoll + getConstitutionModifier());
	setCurrentHp(getMaxHp());
	level_++;
}

template <typename HitDiceType>
void BasicCharacter<HitDiceType>::takeDamage(int damage) {
	setCurrentHp(getCurrentHp() - damage);
}

template <typename HitDiceType>
bool BasicCharacter<HitDiceType>::hasSaveProficiency(stats::AbilityId ability) const {
	return saveProficiencies_.contains(ability);
}

template <typename HitDiceType>
void BasicCharacter<HitDiceType>::addSaveProficiency(stats::AbilityId ability) {
	saveProficiencies_.insert(ability);
}

template <typename HitDiceType>
void BasicCharacter<HitDiceType>::removeSaveProficiency(stats::AbilityId ability) {
	saveProficiencies_.erase(ability);
}

template<typename HitDiceType>
int BasicCharacter<HitDiceType>::rollInitiative() {
	return utils::dice::d20.roll() + getDexterityModifier();
}

template<typename HitDiceType>
int BasicCharacter<HitDiceType>::rollSavingThrow(stats::AbilityId ability) {
	int saveRoll = utils::dice::d20.roll() + getAbility(ability).getModifier();
	if (hasSaveProficiency(ability))
		saveRoll += getProficiencyBonus();
	return saveRoll;
}

template <typename HitDiceType>
int BasicCharacter<HitDiceType>::getNumAttacksPerAction() const {
	return 1;
}

template <typename HitDiceType>
std::tuple<int, int, bool> BasicCharacter<HitDiceType>::rollUnarmedAttack() {
	int natRoll = utils::dice::d20.roll();
	int totalRoll = natRoll + getProficiencyBonus() + getStrengthModifier();
	bool isCrit = natRoll == 20;
	bool isCritMiss = natRoll == 1;
	if (isCritMiss)
		return {natRoll, 0, false};
	return {natRoll, totalRoll, isCrit};
}

template <typename HitDiceType>
int BasicCharacter<HitDiceType>::rollUnarmedDamage(bool crit) {
	return 1 * (crit ? 2 : 1) + getStrengthModifier();
}

}



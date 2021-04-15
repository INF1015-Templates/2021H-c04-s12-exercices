#pragma once


#include <cstddef>
#include <cstdint>

#include <utility>
#include <span>

#include <QString>

#include <stats/StatBlock.hpp>


namespace characters {

class AbstractCharacter : public stats::StatBlock {
public:
	virtual ~AbstractCharacter() = default;

	virtual const QString& getName() const = 0;
	virtual const QString& getClassName() const = 0;
	virtual int getLevel() const = 0;
	virtual int getProficiencyBonus() const = 0;
	virtual void levelUp(bool useAverageHitDie) = 0;
	virtual void takeDamage(int damage) = 0;
	virtual bool hasSaveProficiency(stats::AbilityId ability) const = 0;
	virtual void addSaveProficiency(stats::AbilityId ability) = 0;
	virtual void removeSaveProficiency(stats::AbilityId ability) = 0;
	virtual int rollInitiative() = 0;
	virtual int rollSavingThrow(stats::AbilityId ability) = 0;
	virtual int getNumAttacksPerAction() const = 0;
	virtual std::tuple<int, int, bool> rollUnarmedAttack() = 0;
	virtual int rollUnarmedDamage(bool crit) = 0;
};

}



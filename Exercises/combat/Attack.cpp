
#include <cstddef>
#include <cstdint>

#include <utility>

#include <QObject>
#include <QString>

#include <cppitertools/itertools.hpp>

#include <characters/AbstractCharacter.hpp>
#include <combat/IActivity.hpp>

#include "Attack.hpp"


namespace combat {

Attack::Attack(characters::AbstractCharacter* character, const QString& name, const QString& description, bool multi)
: BaseActivity(character, name, description),
  multiAttack_(multi) { }

void Attack::apply(characters::AbstractCharacter* target) {
	int numStrikes = multiAttack_ ? character_->getNumAttacksPerAction() : 1;
	emit message(tr("%1: %2x").arg(getName()).arg(numStrikes));
	for (int i : iter::range(numStrikes)) {
		auto&& [natRoll, attackRoll, crit] = rollAttack();
		int bonusTotal = attackRoll - natRoll;
		emit message(tr("%1 : [%2] + %3 = %4").arg(getName()).arg(natRoll).arg(bonusTotal).arg(attackRoll));
		if (crit or attackRoll >= target->getArmorClass()) {
			emit message(tr("Hit%1").arg(crit ? tr(" (CRIT)") : tr("")));
			int damage = rollDamage(crit);
			emit message(tr("Damage: %1").arg(damage));
			target->takeDamage(damage);
		} else {
			emit message(tr("Miss"));
		}
	}
	emit done();
}

}



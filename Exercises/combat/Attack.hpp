#pragma once


#include <cstddef>
#include <cstdint>

#include <utility>

#include <QObject>
#include <QString>

#include <characters/AbstractCharacter.hpp>
#include <combat/BaseActivity.hpp>


namespace combat {

class Attack : public BaseActivity<characters::AbstractCharacter> {
	Q_OBJECT

public:
	Attack(characters::AbstractCharacter* character, const QString& name, const QString& description, bool multi);

	void apply(characters::AbstractCharacter* target) override;

signals:
	void rolledAttack(const QString& name, int natRoll, int totalRoll, bool crit);
	void hit(bool crit);
	void miss();
	void rolledDamage(int damage);

protected:
	virtual std::tuple<int, int, bool> rollAttack() = 0;
	virtual int rollDamage(bool crit) = 0;

	bool multiAttack_;
};

}



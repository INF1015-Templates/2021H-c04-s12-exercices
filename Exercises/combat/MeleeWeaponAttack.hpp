#pragma once


#include <cstddef>
#include <cstdint>

#include <utility>

#include <QObject>
#include <QString>

#include <characters/MeleeWeaponUser.hpp>
#include <combat/Attack.hpp>


namespace combat {

class MeleeWeaponAttack : public Attack {
	Q_OBJECT

public:
	MeleeWeaponAttack(characters::MeleeWeaponUser* character, bool multi);

	bool isAvailable() const override;

protected:
	std::tuple<int, int, bool> rollAttack() override;
	int rollDamage(bool crit) override;

private:
	characters::MeleeWeaponUser* weaponUser_;
};

}



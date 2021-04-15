#pragma once


#include <cstddef>
#include <cstdint>

#include <type_traits>

#include <weapons/melee/IMeleeWeapon.hpp>
#include <utils/DiceRoller.hpp>


namespace weapons::melee {

template <int numDmgDice, typename DmgDie1H, typename DmgDie2H, bool twoHanded, bool martial>
class GenericMeleeWeapon : public IMeleeWeapon {
public:
	GenericMeleeWeapon(const QString& name, int bonus = 0)
	: name_(name),
	  bonus_(bonus) { }

	const QString& getName() const override { return name_; }
	int getAttackBonus() const override { return bonus_; }
	int getDamageBonus() const override { return getAttackBonus(); }

	virtual std::pair<int, int> rollDamage() {
		if (wieldingTwoHanded_)
			return {(numDmgDice * damageDie2H_).roll(), getDamageBonus()};
		else
			return {(numDmgDice * damageDie1H_).roll(), getDamageBonus()};
	}

	bool isMartial() const override {
		return martial;
	}

	bool isVersatile() const override {
		return not isTwoHanded() and not std::is_same_v<DmgDie1H, DmgDie2H>;
	}

	bool isTwoHanded() const override {
		return twoHanded;
	}

	void wieldOneHanded() override {
		if (isTwoHanded())
			// TODO: Gestion d'erreur?
			return;
		wieldingTwoHanded_ = false;
	}

	void wieldTwoHanded() override {
		if (not (isTwoHanded() or isVersatile()))
			// TODO: Gestion d'erreur?
			return;
		wieldingTwoHanded_ = true;
	}

private:
	QString name_;
	int bonus_;
	bool wieldingTwoHanded_ = twoHanded;
	DmgDie1H damageDie1H_{};
	DmgDie2H damageDie2H_{};
};


template <int numDmgDice, typename DmgDie, bool martial>
using GenericOneHandedWeapon = GenericMeleeWeapon<numDmgDice, DmgDie, DmgDie, false, martial>;

template <int numDmgDice, typename DmgDie, bool martial>
using GenericTwoHandedWeapon = GenericMeleeWeapon<numDmgDice, DmgDie, DmgDie, true, martial>;

template <int numDmgDice, typename DmgDie1H, typename DmgDie2H, bool martial>
using GenericVersatileWeapon = GenericMeleeWeapon<numDmgDice, DmgDie1H, DmgDie2H, false, martial>;


using namespace utils::dice;

// Built-in simple weapons
using Club         = GenericOneHandedWeapon<1, d4_t, false>;
using Dagger       = GenericOneHandedWeapon<1, d4_t, false>;
using Greatclub    = GenericTwoHandedWeapon<1, d8_t, false>;
using Handaxe      = GenericOneHandedWeapon<1, d6_t, false>;
using Javelin      = GenericOneHandedWeapon<1, d6_t, false>;
using LightHammer  = GenericOneHandedWeapon<1, d4_t, false>;
using Mace         = GenericOneHandedWeapon<1, d6_t, false>;
using Quarterstaff = GenericVersatileWeapon<1, d6_t, d8_t, false>;
using Sickle       = GenericOneHandedWeapon<1, d4_t, false>;
using Spear        = GenericVersatileWeapon<1, d6_t, d8_t, false>;

// Built-in martial weapons
using Battleaxe   = GenericVersatileWeapon<1, d8_t, d10_t, true>;
using Flail       = GenericOneHandedWeapon<1, d8_t, true>;
using Glaive      = GenericTwoHandedWeapon<1, d10_t, true>;
using Greataxe    = GenericTwoHandedWeapon<1, d12_t, true>;
using Greatsword  = GenericTwoHandedWeapon<2, d6_t, true>;
using Halberd     = GenericTwoHandedWeapon<1, d10_t, true>;
using Lance       = GenericTwoHandedWeapon<1, d12_t, true>;
using Longsword   = GenericVersatileWeapon<1, d8_t, d10_t, true>;
using Maul        = GenericTwoHandedWeapon<2, d6_t, true>;
using Morningstar = GenericOneHandedWeapon<1, d8_t, true>;
using Pike        = GenericTwoHandedWeapon<1, d10_t, true>;
using Rapier      = GenericOneHandedWeapon<1, d8_t, true>;
using Scimitar    = GenericOneHandedWeapon<1, d6_t, true>;
using Shortsword  = GenericOneHandedWeapon<1, d6_t, true>;
using Trident     = GenericVersatileWeapon<1, d6_t, d8_t, true>;
using WarPick     = GenericOneHandedWeapon<1, d8_t, true>;
using Warhammer   = GenericVersatileWeapon<1, d8_t, d10_t, true>;
using Whip        = GenericOneHandedWeapon<1, d4_t, true>;

}


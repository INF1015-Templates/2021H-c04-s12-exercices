#pragma once


#include <cstddef>
#include <cstdint>

#include <utility>
#include <memory>
#include <vector>

#include <QObject>
#include <QString>

#include <combat/Turn.hpp>
#include <combat/classes/MonkTurn.hpp>
#include <combat/classes/FighterTurn.hpp>
#include <weapons/melee/GenericMeleeWeapon.hpp>

#include "CombatManager.hpp"


namespace combat {

CombatManager::CombatManager() {
	
}

Turn* CombatManager::getCurrentTurn() const {
	return turns_[0];
}

Turn* CombatManager::getNpcTurn() const {
	return npcTurn_.get();
}

Turn* CombatManager::getPlayerTurn() const {
	return playerTurn_.get();
}

characters::AbstractCharacter* CombatManager::getNpcCharacter() const {
	return npcCharacter_.get();
}

characters::AbstractCharacter* CombatManager::getPlayerCharacter() const {
	return playerCharacter_.get();
}

void CombatManager::init() {
	loadCharacters();

	int npcInitiative = npcCharacter_->rollInitiative();
	int playerInitiative = playerCharacter_->rollInitiative();
	if (playerInitiative > npcInitiative)
		turns_ = {playerTurn_.get(), npcTurn_.get()};
	else 
		turns_ = {npcTurn_.get(), playerTurn_.get()};

	connect(playerTurn_.get(), SIGNAL(ended()), this, SLOT(startNextTurn()));
	connect(npcTurn_.get(), SIGNAL(ended()), this, SLOT(startNextTurn()));
	connect(playerTurn_.get(), SIGNAL(ended()), this, SLOT(checkCharacterDeath()));
	connect(npcTurn_.get(), SIGNAL(ended()), this, SLOT(checkCharacterDeath()));
}

void CombatManager::loadCharacters() {
	static const int charLevel = 20;

	auto staff      = std::make_unique<weapons::melee::Quarterstaff>("Quarterstaff +1", +1);
	auto shortsword = std::make_unique<weapons::melee::Shortsword>("Shortsword +1", +1);
	auto greatsword = std::make_unique<weapons::melee::Greatsword>("Greatsword +1", +1);

	stats::Ability abilities1[] = {
		{stats::STR, 10},
		{stats::DEX, 20},
		{stats::CON, 14},
		{stats::INT, 12},
		{stats::WIS, 16},
		{stats::CHA, 8}
	};
	auto monk1 = std::make_unique<characters::classes::Monk>("Fast Boi", abilities1);
	monk1->equipWeapon(std::move(staff));
	monk1->getWeapon()->wieldTwoHanded();

	stats::Ability abilities2[] = {
		{stats::STR, 18},
		{stats::DEX, 13},
		{stats::CON, 16},
		{stats::INT, 10},
		{stats::WIS, 10},
		{stats::CHA, 8}
	};
	auto fighter1 = std::make_unique<characters::classes::Fighter>("Stronk Boi", abilities2);
	fighter1->equipWeapon(std::move(greatsword));
	fighter1->setArmorClass(18);

	stats::Ability abilities3[] = {
		{stats::STR,  8},
		{stats::DEX, 16},
		{stats::CON, 12},
		{stats::INT, 10},
		{stats::WIS, 18},
		{stats::CHA,  8}
	};
	auto monk2 = std::make_unique<characters::classes::Monk>("Other Fast Boi", abilities3);
	monk2->equipWeapon(std::move(shortsword));

	for (int i : iter::range(charLevel - 1)) {
		monk1->levelUp(true);
		fighter1->levelUp(true);
		monk2->levelUp(true);
	}

	playerTurn_ = std::make_unique<classes::MonkTurn>(monk1.get(), monk2.get());
	npcTurn_ = std::make_unique<classes::MonkTurn>(monk2.get(), monk1.get());
	playerCharacter_ = std::move(monk1);
	//playerTurn_ = std::make_unique<classes::FighterTurn>(fighter1.get(), monk2.get());
	//npcTurn_ = std::make_unique<classes::MonkTurn>(monk2.get(), fighter1.get());
	//playerCharacter_ = std::move(fighter1);
	npcCharacter_ = std::move(monk2);
}

void CombatManager::startCurrentTurn() {
	if (gameOver_)
		return;
	turns_[0]->start();
	if (getCurrentTurn() == getNpcTurn()) {
		// Whatever on fait toutes les attaques.
		getCurrentTurn()->takeAction(1);
		getCurrentTurn()->takeBonusAction(0);
	}
}

void CombatManager::startNextTurn() {
	std::swap(turns_[0], turns_[1]);
	startCurrentTurn();
}

void CombatManager::checkCharacterDeath() {
	if (gameOver_)
		return;
	for (auto&& ch : {playerCharacter_.get(), npcCharacter_.get()}) {
		if (ch->getCurrentHp() == 0) {
			gameOver_ = true;
			emit characterDied(ch);
		}
	}
}

}



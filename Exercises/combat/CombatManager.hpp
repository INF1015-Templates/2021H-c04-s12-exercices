#pragma once


#include <cstddef>
#include <cstdint>

#include <utility>
#include <memory>
#include <vector>

#include <QObject>
#include <QString>

#include <combat/Turn.hpp>
#include <combat/IActivity.hpp>


namespace combat {

class CombatManager : public QObject {
	Q_OBJECT

public:
	CombatManager();

	Turn* getCurrentTurn() const;
	Turn* getNpcTurn() const;
	Turn* getPlayerTurn() const;
	characters::AbstractCharacter* getNpcCharacter() const;
	characters::AbstractCharacter* getPlayerCharacter() const;

	void init();
	void loadCharacters();

public slots:
	void startCurrentTurn();
	void startNextTurn();
	void checkCharacterDeath();

signals:
	void message(const QString&);
	void characterDied(characters::AbstractCharacter*);

private:
	std::unique_ptr<characters::AbstractCharacter> npcCharacter_;
	std::unique_ptr<characters::AbstractCharacter> playerCharacter_;
	std::unique_ptr<Turn> npcTurn_;
	std::unique_ptr<Turn> playerTurn_;
	std::vector<Turn*> turns_;
	bool gameOver_ = false;
};

}



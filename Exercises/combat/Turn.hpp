#pragma once


#include <cstddef>
#include <cstdint>

#include <utility>
#include <memory>
#include <vector>

#include <QObject>
#include <QString>

#include <characters/AbstractCharacter.hpp>
#include <combat/fwddecl.hpp>


namespace combat {

class Turn : public QObject {
	Q_OBJECT

public:
	static constexpr int skipActivity = -1;

	Turn(characters::AbstractCharacter* character, characters::AbstractCharacter* opponent);

	virtual ~Turn() = default;

	std::span<IActivity*> getActions();
	std::span<IActivity*> getBonusActions();
	bool isActionAvailable() const;
	bool isBonusActionAvailable() const;
	characters::AbstractCharacter* getCharacter() const;
	characters::AbstractCharacter* getOpponent() const;

public slots:
	virtual void start();
	virtual void takeAction(int index);
	virtual void takeBonusAction(int index);
	virtual void end();

signals:
	void message(const QString&);
	void started();
	void actionTaken();
	void bonusActionTaken();
	void ended();

protected:
	characters::AbstractCharacter* character_;
	characters::AbstractCharacter* opponent_;
	std::vector<IActivity*> actions_;
	std::vector<IActivity*> bonusActions_;
	bool actionAvailable_ = false;
	bool bonusActionAvailable_ = false;
};

}



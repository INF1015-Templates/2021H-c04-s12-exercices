#pragma once


#include <cstddef>
#include <cstdint>

#include <utility>

#include <QObject>
#include <QString>

#include <characters/AbstractCharacter.hpp>
#include <combat/fwddecl.hpp>


namespace combat {

class IActivity : public QObject {
	Q_OBJECT

public:
	virtual ~IActivity() = default;

	virtual const QString& getName() const = 0;
	virtual const QString& getDescription() const = 0;
	virtual characters::AbstractCharacter* getCharacter() const = 0;
	virtual void connectWithTurn(Turn*) { };
	virtual bool isAvailable() const = 0;
	virtual void apply(characters::AbstractCharacter* target) = 0;

signals:
	void done();
	void message(const QString& msg);
};

}



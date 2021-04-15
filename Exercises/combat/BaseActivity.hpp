#pragma once


#include <cstddef>
#include <cstdint>

#include <utility>

#include <QObject>
#include <QString>

#include <combat/IActivity.hpp>


namespace combat {

template <typename CharType>
class BaseActivity : public IActivity {
public:
	BaseActivity(CharType* character, const QString& name, const QString& description = "N/A")
	: name_(name),
	  description_(description),
	  character_(character) { }

	const QString& getName() const override {
		return name_;
	}

	const QString& getDescription() const override {
		return description_;
	}
	
	characters::AbstractCharacter* getCharacter() const override {
		return character_;
	}

protected:
	QString name_;
	QString description_;
	CharType* character_;
};

}



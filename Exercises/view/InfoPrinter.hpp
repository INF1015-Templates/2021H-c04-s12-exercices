#include <QObject>
#include <QString>
#include <QDebug>


namespace view {

class Printer : public QObject {
	Q_OBJECT

public:
	Printer() { }

public slots:
	void printMsg(const QString& txt) {
		qInfo() << txt;
	}
};

}

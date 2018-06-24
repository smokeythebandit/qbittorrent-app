#ifndef BACKEND_H
#define BACKEND_H

//Qt framework
#include <QObject>
#include <QQmlEngine>

//Internal headers
#include "WebConnector.h"
#include "GlobalTransferInfo.h"

class Backend : public QObject
{
		Q_OBJECT
	public:
		explicit Backend(QObject *parent = nullptr);

		static QObject *webConnector(QQmlEngine *engine, QJSEngine *scriptEngine);
		static QObject *globalTransferInfo(QQmlEngine *engine, QJSEngine *scriptEngine);

		static QNetworkAccessManager *networkAccessManager();

	private:
};

#endif // BACKEND_H

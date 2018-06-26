#ifndef BACKEND_H
#define BACKEND_H

//Qt framework
#include <QObject>
#include <QQmlEngine>

//Internal headers
#include "Torrents/Torrents.h"
#include "DebugMessageHandler.h"
#include "WebConnector/WebConnector.h"
#include "GlobalTransferInfo/GlobalTransferInfo.h"

class Backend : public QObject
{
		Q_OBJECT
	public:
		explicit Backend(QObject *parent = nullptr);

		static QObject *torrents(QQmlEngine *engine, QJSEngine *scriptEngine);
		static QObject *webConnector(QQmlEngine *engine, QJSEngine *scriptEngine);
		static QObject *globalTransferInfo(QQmlEngine *engine, QJSEngine *scriptEngine);

		static QNetworkAccessManager *networkAccessManager();

	private:
};

#endif // BACKEND_H

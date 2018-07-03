#ifndef BACKEND_H
#define BACKEND_H

//Qt framework
#include <QObject>
#include <QQmlEngine>

//Internal headers
#include "backend_global.h"
#include "DebugMessageHandler.h"
#include "WebConnector/WebConnector.h"
#include "DownloadManager/DownloadManager.h"
#include "GlobalTransferInfo/GlobalTransferInfo.h"

class BACKEND_EXPORT Backend : public QObject
{
		Q_OBJECT
	public:
		explicit Backend(QObject *parent = nullptr);

		static QObject *downloadManager(QQmlEngine *engine, QJSEngine *scriptEngine);
		static QObject *webConnector(QQmlEngine *engine, QJSEngine *scriptEngine);
		static QObject *globalTransferInfo(QQmlEngine *engine, QJSEngine *scriptEngine);
		static QNetworkAccessManager *networkAccessManager();

	private:
};

#endif // BACKEND_H

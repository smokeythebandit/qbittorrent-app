#include "Backend.h"

Backend::Backend(QObject *parent) : QObject(parent)
{

}

QObject *Backend::downloadManager(QQmlEngine *engine, QJSEngine *scriptEngine)
{
	Q_UNUSED(engine)
	Q_UNUSED(scriptEngine)
	static DownloadManager torrents(networkAccessManager());
	return &torrents;
}

QObject *Backend::webConnector(QQmlEngine *engine, QJSEngine *scriptEngine) {
	Q_UNUSED(engine)
	Q_UNUSED(scriptEngine)
	static WebConnector webConnector(networkAccessManager());
	return &webConnector;
}

QObject *Backend::globalTransferInfo(QQmlEngine *engine, QJSEngine *scriptEngine) {
	Q_UNUSED(engine)
	Q_UNUSED(scriptEngine)
	static GlobalTransferInfo globalTransferInfo(networkAccessManager());
	return &globalTransferInfo;
}

QNetworkAccessManager *Backend::networkAccessManager() {
	static QNetworkAccessManager networkAccessManager;
	return &networkAccessManager;
}

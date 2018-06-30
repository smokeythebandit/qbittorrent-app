//Qt framework
#include <QIcon>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

//Internal headers
#include "Backend.h"
#include "qobjectlistmodel.h"
#include "Torrents/DownloadManager.h"
#include "Torrents/Torrent.h"
#include "Torrents/Categorie.h"
#include "WebConnector/WebConnector.h"
#include "GlobalTransferInfo/GlobalTransferInfo.h"

int main(int argc, char *argv[])
{

	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	//Register all classes
    qmlRegisterSingletonType<DownloadManager>("io.backend", 1, 0, "DownloadManager", &Backend::downloadManager);
	qmlRegisterSingletonType<WebConnector>("io.backend", 1, 0, "WebConnector", &Backend::webConnector);
	qmlRegisterSingletonType<GlobalTransferInfo>("io.backend", 1, 0, "GlobalTransferInfo", &Backend::globalTransferInfo);
    qmlRegisterType<Categorie>();
    qmlRegisterType<Torrent>();

    qRegisterMetaType<QGenericListModel<Categorie>*>("QGenericListModel<Categorie>*");
    qRegisterMetaType<QGenericListModel<Torrent>*>("QGenericListModel<Torrent>*");

    QGuiApplication app(argc, argv);
	DebugMessageHandler::createInstance(true);
	app.setWindowIcon(QIcon(":/Icons/Icons/qbittorrent-logo.svg"));
	QCoreApplication::setOrganizationName("qBittorrent");
	QCoreApplication::setOrganizationDomain("qbittorrent.org");
	QCoreApplication::setApplicationName("qBittorrent Mobile Client");

	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}

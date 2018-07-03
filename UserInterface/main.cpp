//Qt framework
#include <QIcon>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

//Internal headers
#include "Backend.h"
#include <QInputDialog>
#include "qobjectlistmodel.h"
#include "DownloadManager/Torrent.h"
#include "DownloadManager/Categorie.h"
#include "WebConnector/WebConnector.h"
#include "DownloadManager/DownloadManager.h"
#include "GlobalTransferInfo/GlobalTransferInfo.h"

int main(int argc, char *argv[])
{

	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	//Register all classes
    qmlRegisterType<Torrent>();
    qmlRegisterType<Categorie>();
    qRegisterMetaType<QGenericListModel<Torrent>*>("QGenericListModel<Torrent>*");
    qRegisterMetaType<QGenericListModel<Categorie>*>("QGenericListModel<Categorie>*");
	qmlRegisterSingletonType<WebConnector>("io.backend", 1, 0, "WebConnector", &Backend::webConnector);
    qmlRegisterSingletonType<DownloadManager>("io.backend", 1, 0, "DownloadManager", &Backend::downloadManager);
	qmlRegisterSingletonType<GlobalTransferInfo>("io.backend", 1, 0, "GlobalTransferInfo", &Backend::globalTransferInfo);


    QGuiApplication app(argc, argv);
	DebugMessageHandler::createInstance(true);
	app.setWindowIcon(QIcon(":/Icons/Icons/qbittorrent-logo.svg"));
	QCoreApplication::setOrganizationName("qBittorrent");
	QCoreApplication::setOrganizationDomain("qbittorrent.org");
	QCoreApplication::setApplicationName("qBittorrent Mobile Client");

	QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/QML");
    engine.load(QUrl(QStringLiteral("qrc:/QML/main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}

#include "Backend/WebConnector.h"
#include <QIcon>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{

//	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	//Register all classes
	qmlRegisterType<WebConnector>("io.backend", 1, 0, "WebConnector");

	QGuiApplication app(argc, argv);
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

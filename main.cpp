#include <QIcon>
#include <Backend/Backend.h>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{

	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	//Register all classes
	qmlRegisterSingletonType<Torrents>("io.backend", 1, 0, "Torrents", &Backend::torrents);
	qmlRegisterSingletonType<WebConnector>("io.backend", 1, 0, "WebConnector", &Backend::webConnector);
	qmlRegisterSingletonType<GlobalTransferInfo>("io.backend", 1, 0, "GlobalTransferInfo", &Backend::globalTransferInfo);

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

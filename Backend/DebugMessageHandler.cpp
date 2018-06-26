#include "DebugMessageHandler.h"

	DebugMessageHandler::DebugMessageHandler(bool timestamps, QObject *parent) : QObject(parent)
	{
		if(timestamps) {
			qInstallMessageHandler(&DebugMessageHandler::messageHandlerTimeStamped);
		} else {
			qInstallMessageHandler(&DebugMessageHandler::messageHandler);
		}
	}

	DebugMessageHandler *DebugMessageHandler::getInstance(const bool timestamps) {
		static DebugMessageHandler instance(timestamps);
		return &instance;
	}

	DebugMessageHandler *DebugMessageHandler::createInstance(const bool timestamps) {
		return getInstance(timestamps);
	}

	void DebugMessageHandler::messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &message) {
		Q_UNUSED(context);
		switch(type)
		{
			case QtDebugMsg:
				std::cout << addTypePadding(typeToString(type)).toStdString()  << " " << message.toStdString() << std::endl;
			break;
			case QtInfoMsg:
				std::cout << addTypePadding(typeToString(type)).toStdString() << " " << message.toStdString() << std::endl;
			break;
			case QtWarningMsg:
				std::cout << addTypePadding(typeToString(type)).toStdString() << " " << message.toStdString() << std::endl;
			break;
			case QtCriticalMsg:
				std::cout << addTypePadding(typeToString(type)).toStdString() << " " << message.toStdString() << std::endl;
			break;
			case QtFatalMsg:
				std::cout << addTypePadding(typeToString(type)).toStdString() << " " << message.toStdString() << std::endl;
			break;
			default:
				std::cout << addTypePadding(typeToString(type)).toStdString() << " " << message.toStdString() << std::endl;

		}
		emit getInstance()->newDebugMessage(type, message);
	}

	void DebugMessageHandler::messageHandlerTimeStamped(QtMsgType type, const QMessageLogContext &context, const QString &message) {
		Q_UNUSED(context);
		switch(type)
		{
			case QtDebugMsg:
				std::cout << QDateTime::currentDateTime().toString("HH:mm:ss dd.MM.yyyy").toStdString() << " " << addTypePadding(typeToString(type)).toStdString() << " " << message.toStdString() << std::endl;
			break;
			case QtInfoMsg:
				std::cout << QDateTime::currentDateTime().toString("HH:mm:ss dd.MM.yyyy").toStdString() << " " << addTypePadding(typeToString(type)).toStdString() << " " << message.toStdString() << std::endl;
			break;
			case QtWarningMsg:
				std::cout << QDateTime::currentDateTime().toString("HH:mm:ss dd.MM.yyyy").toStdString() << addTypePadding(typeToString(type)).toStdString() << " " << message.toStdString() << std::endl;
			break;
			case QtCriticalMsg:
				std::cout << QDateTime::currentDateTime().toString("HH:mm:ss dd.MM.yyyy").toStdString() << " " << addTypePadding(typeToString(type)).toStdString() << " " << message.toStdString() << std::endl;
			break;
			case QtFatalMsg:
				std::cout << QDateTime::currentDateTime().toString("HH:mm:ss dd.MM.yyyy").toStdString() << " " << addTypePadding(typeToString(type)).toStdString() << " " << message.toStdString() << std::endl;
			break;
			default:
				std::cout << QDateTime::currentDateTime().toString("HH:mm:ss dd.MM.yyyy").toStdString() << " " << addTypePadding(typeToString(type)).toStdString() << " " << message.toStdString() << std::endl;

		}
		emit getInstance()->newDebugMessage(type, message);
	}

	QString DebugMessageHandler::typeToString(QtMsgType type) {
		switch(type)
		{
			case QtDebugMsg:
				return "Debug";
			case QtInfoMsg:
				return "Info";
			case QtWarningMsg:
				return "Warning";
			case QtCriticalMsg:
				return "Critical";
			case QtFatalMsg:
				return "Fatal";
			default:
				return "Unknown";
		}
	}

	QString DebugMessageHandler::addTypePadding(QString message) {
		QString returnMessage = "[" + message;
		static quint8 size = 10;
		while(returnMessage.length() < size - 1)
		{
			returnMessage.append(" ");
		}
		returnMessage.append("]");
		return returnMessage;
	}

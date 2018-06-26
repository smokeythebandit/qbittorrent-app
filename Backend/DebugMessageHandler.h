#ifndef DEBUGMESSAGEHANDLER_H
#define DEBUGMESSAGEHANDLER_H

//Qt Framework
#include <QMutex>
#include <QObject>
#include <QDateTime>

//Stabdard libraries
#include <stdint.h>
#include <iostream>

class DebugMessageHandler : public QObject
{
		Q_OBJECT
	public:
		static DebugMessageHandler *getInstance(const bool timestamps = false);
		static DebugMessageHandler *createInstance(const bool timestamps = false);

	protected:
		static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &message);
		static void messageHandlerTimeStamped(QtMsgType type, const QMessageLogContext &context, const QString &message);
		static QString typeToString(QtMsgType type);
		static QString addTypePadding(QString message);

		signals:
			void newDebugMessage(quint32 type, const QString &string);

		private:
			explicit DebugMessageHandler(bool timestamps, QObject *parent = 0);
};

#endif // DEBUGMESSAGEHANDLER_H

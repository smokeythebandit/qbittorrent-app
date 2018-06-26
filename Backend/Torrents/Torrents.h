#ifndef TORRENTS_H
#define TORRENTS_H

//Qt framework
#include <QObject>
#include <QUrlQuery>
#include <QJsonObject>

//STD framework
#include <functional>

//Internal headers
#include "../AbstractApiInterface.h"

class Torrents : public AbstractApiInterface
{
		Q_OBJECT
	public:
		enum Status {All, Downloading, Completed, Paused, Active, Inactive};
		Torrents(QNetworkAccessManager *networkAccessManager, QObject *parent = nullptr);

		Q_ENUM(Status)

	private:
		void getPartialData(std::function<void(const QJsonObject&)> callback);
		void processTorrents(const QJsonObject &torrents, const QJsonArray &removedTorrents);

	private slots:
		void update();

	private:
		QStringListModel m_categories;
		QHash<QString, QString> m_torrents;
		qint64 m_rid; ///< Contains the response ID of last recieved partialdata
};

#endif // TORRENTS_H

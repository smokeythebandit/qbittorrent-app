#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

//Qt framework
#include <QObject>
#include <QUrlQuery>
#include <QJsonObject>
#include <QStringList>
#include <QStringListModel>

//STD framework
#include <functional>

//Libraries
#include "qobjectlistmodel.h"

//Internal headers
#include "Torrent.h"
#include "Categorie.h"
#include "../backend_global.h"
#include "../AbstractApiInterface.h"

class BACKEND_EXPORT DownloadManager : public AbstractApiInterface
{
		Q_OBJECT
	public:
		enum Status {All, Downloading, Completed, Paused, Active, Inactive};

		Q_ENUM(Status)
        Q_PROPERTY(QGenericListModel<Categorie> *categories READ categories NOTIFY categoriesChanged)
        Q_PROPERTY(QGenericListModel<Torrent> *torrents READ torrents NOTIFY torrentsChanged)

        DownloadManager(QNetworkAccessManager *networkAccessManager, QObject *parent = nullptr);

        QGenericListModel<Categorie> *categories();

        QGenericListModel<Torrent> *torrents();

    private:
        void getPartialData(std::function<void(const QJsonObject&)> callback);
		void processTorrents(const QJsonObject &torrents, const QJsonArray &removedTorrents);
		void processCategories(const QJsonArray &categories, const QJsonArray &removedCategories);
        static void processTorrentData(const QJsonObject &responseData, Torrent* torrent);

	signals:
		void categoriesChanged();
        void torrentsChanged();

	private slots:
		void update();

	private:
        QGenericListModel<Categorie> m_categories;
        QGenericListModel<Torrent> m_torrents;
		qint64 m_rid; ///< Contains the response ID of last recieved partialdata
};

#endif // DOWNLOADMANAGER_H

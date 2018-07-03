#include "DownloadManager.h"

DownloadManager::DownloadManager(QNetworkAccessManager *networkAccessManager, QObject *parent) : AbstractApiInterface(networkAccessManager, parent),
    m_categories(true, this), m_torrents(true, this), m_rid(0)
{
    m_updateTimer.start(500);
    connect(&m_categories, &QGenericListModel<Categorie>::dataChanged, this, &DownloadManager::categoriesChanged);
    connect(&m_torrents, &QGenericListModel<Torrent>::dataChanged, this, &DownloadManager::torrentsChanged);

}

void DownloadManager::getPartialData(std::function<void (const QJsonObject &)> callback) {
	QUrlQuery urlQuery;
	urlQuery.addQueryItem("rid", QString::number(m_rid));
    get(urlWithPath("/sync/maindata?" + urlQuery.query()), [=] (QNetworkReply *reply) {
		if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 200) {
			QJsonDocument	jsonDocument	= QJsonDocument::fromJson(reply->readAll());
			callback(jsonDocument.object());
		} else callback(QJsonObject());
	});
}

void DownloadManager::processCategories(const QJsonArray &categories, const QJsonArray &removedCategories) {
	//Adding new categories
	foreach(const QVariant &categorie, categories.toVariantList()) {
        m_categories.insertObject(m_categories.rowCount(), new Categorie(categorie.toString(), m_networkAccessManager, this));
	}
	//Remove old categories
	foreach(const QVariant &removedCategorie, removedCategories.toVariantList()) {
        foreach(Categorie* categorie, m_categories.objects()) {
            if(categorie->name() == removedCategorie) {
                m_categories.removeObject(m_categories.index(categorie));
                break;
            }
        }
    }
}

void DownloadManager::processTorrentData(const QJsonObject &responseData, Torrent *torrent)
{
    //Map the values from the responce to the properties of Torrent
    QHash<QString, QString> jsonToPropertyMapping;
    jsonToPropertyMapping.insert("name", "name");
    jsonToPropertyMapping.insert("size", "size");
    jsonToPropertyMapping.insert("progress", "progress");
    jsonToPropertyMapping.insert("dlspeed", "downloadSpeed");
    jsonToPropertyMapping.insert("upspeed", "uploadSpeed");
    jsonToPropertyMapping.insert("priority", "priority");
    jsonToPropertyMapping.insert("num_seeds", "numberConnectedSeeds");
    jsonToPropertyMapping.insert("num_complete", "numberCompletedSeeds");
    jsonToPropertyMapping.insert("num_leechs", "numberLeechers");
    jsonToPropertyMapping.insert("num_incomplete", "numberIncompletedSeeds");
    jsonToPropertyMapping.insert("ratio", "ratio");
    jsonToPropertyMapping.insert("eta", "eta");
    jsonToPropertyMapping.insert("state", "state");
    jsonToPropertyMapping.insert("seq_dl", "sequentialDownload");
    jsonToPropertyMapping.insert("f_l_piece_prio", "lastPiecePriority");
    jsonToPropertyMapping.insert("category", "category");
    jsonToPropertyMapping.insert("super_seeding", "superSeeding");
    jsonToPropertyMapping.insert("force_start", "forceStart");

    //Update values
    foreach(const QString key, responseData.keys()) {
        if(jsonToPropertyMapping.contains(key)) {
            if(!torrent->setProperty(jsonToPropertyMapping[key].toLatin1(), responseData[key].toVariant())) {
                qDebug() << "Failed to process message value" << key << "mapped to" << jsonToPropertyMapping[key];
            }
        }
    }
}

void DownloadManager::processTorrents(const QJsonObject &torrents, const QJsonArray &removedTorrents) {
	QVariantList removedTorrentsList = removedTorrents.toVariantList();
	//Adding new torrents
	foreach (const QString &torrentHash, torrents.keys()) {
        bool torrentExists = false;
        Torrent* existingTorrent = nullptr;
        foreach(Torrent* torrent, m_torrents.objects()) {
            if(torrent->hash() == torrentHash) {
                existingTorrent = torrent;
                torrentExists = true;
                break;
            }
        }
        if(torrentExists) {
            processTorrentData(torrents[torrentHash].toObject(), existingTorrent);
            continue;
        } else {
            Torrent* newTorrent = new Torrent(torrentHash, m_networkAccessManager, this);
            processTorrentData(torrents[torrentHash].toObject(), newTorrent);
            m_torrents.insertObject(m_torrents.rowCount(), newTorrent);
        }


    }
	//Removing old torrents
	foreach (const QVariant &removedTorrentHash, removedTorrentsList) {
        foreach(Torrent* torrent, m_torrents.objects()) {
            if(torrent->hash() == removedTorrentHash) {
                m_torrents.removeObject(m_torrents.index(torrent));
                break;
            }
        }
	}
}

void DownloadManager::update() {
	getPartialData( [=] (const QJsonObject &partialData) {
		if(!partialData.isEmpty()) {
			m_rid = partialData["rid"].toInt();
			//Process torrents
			QJsonObject torrents = partialData["torrents"].toObject();
			QJsonArray removedTorrents = partialData["torrents_removed"].toArray();
			processTorrents(torrents, removedTorrents);
			//Process categories
			QJsonArray categories = partialData["categories"].toArray();
			QJsonArray removedCategories = partialData ["categories_removed"].toArray();
			processCategories(categories, removedCategories);
		}
	});
}

QGenericListModel<Torrent> *DownloadManager::torrents() {
    return &m_torrents;
}

QGenericListModel<Categorie> *DownloadManager::categories() {
    return &m_categories;
}

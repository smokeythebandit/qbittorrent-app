#include "Torrents.h"

Torrents::Torrents(QNetworkAccessManager *networkAccessManager, QObject *parent) : AbstractApiInterface(networkAccessManager, parent), m_rid(0)
{
	m_updateTimer.start(1000);
}

void Torrents::getPartialData(std::function<void (const QJsonObject &)> callback) {
	QUrlQuery urlQuery;
	urlQuery.addQueryItem("rid", QString::number(m_rid));
	get(urlWithPath("/sync/maindata?" + urlQuery.query()), [=](QNetworkReply *reply) {
		if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 200) {
			QJsonDocument	jsonDocument	= QJsonDocument::fromJson(reply->readAll());
			callback(jsonDocument.object());
		} else callback(QJsonObject());
	});
}

void Torrents::processTorrents(const QJsonObject &torrents, const QJsonArray &removedTorrents) {
	QVariantList removedTorrentsList = removedTorrents.toVariantList();
	//Adding new torrents
	foreach (const QString &torrentHash, torrents.keys()) {
		if(m_torrents.contains(torrentHash)) m_torrents.insert(torrentHash, torrentHash);
	}
	//Removing old torrents
	foreach (const QVariant &removedTorrentHash, removedTorrentsList) {
		m_torrents.remove(removedTorrentHash.toString());
	}
}

void Torrents::update() {
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

		}
	});
}

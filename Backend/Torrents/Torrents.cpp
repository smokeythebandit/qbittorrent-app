#include "Torrents.h"

Torrents::Torrents(QNetworkAccessManager *networkAccessManager, QObject *parent) : AbstractApiInterface(networkAccessManager, parent), m_rid(0)
{
	m_updateTimer.start(100);
	connect(&m_categories, &QStringListModel::dataChanged, this, &Torrents::categoriesChanged);
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

void Torrents::processCategories(const QJsonArray &categories, const QJsonArray &removedCategories)
{
	//Adding new categories
	foreach(const QVariant &categorie, categories.toVariantList()) {
		if(!m_categories.stringList().contains(categorie.toString())) {
			m_categories.insertRow(m_categories.rowCount());
			QModelIndex index = m_categories.index(m_categories.rowCount() - 1, 0);
			m_categories.setData(index, categorie);
		}
	}
	//Remove old categories
	foreach(const QVariant &removedCategorie, removedCategories.toVariantList()) {
		if(m_categories.stringList().contains(removedCategorie.toString())) {
			QModelIndex index = m_categories.match(m_categories.index(0,0), Qt::DisplayRole, removedCategorie, 2, Qt::MatchRecursive).first();
			m_categories.removeRow(index.row());
		}
	}
	m_categories.sort(0, Qt::AscendingOrder);
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
			processCategories(categories, removedCategories);
		}
	});
}

QStringListModel *Torrents::categories() {
	return &m_categories;
}

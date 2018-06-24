#include "GlobalTransferInfo.h"

GlobalTransferInfo::GlobalTransferInfo(QNetworkAccessManager *networkAccessManager, QObject *parent) : QObject(parent),
	m_networkAccessManager(networkAccessManager)
{
	connect(&m_updateTimer, &QTimer::timeout, this, &GlobalTransferInfo::update);
	m_updateTimer.start(500);
}

QString GlobalTransferInfo::transferSpeed() const {
	QLocale locale;
	QString transferSpeed = "↑%1/s\n↓%2/s";
	return transferSpeed.arg(locale.formattedDataSize(uploadRate(), 1, QLocale::DataSizeSIFormat), locale.formattedDataSize(downloadRate(), 1, QLocale::DataSizeSIFormat));
}

quint64 GlobalTransferInfo::downloadedBytes() const {
	return m_downloadedBytes;
}

quint64 GlobalTransferInfo::uploadedBytes() const {
	return m_uploadedBytes;
}

quint64 GlobalTransferInfo::downloadRate() const {
	return m_downloadRate;
}

quint64 GlobalTransferInfo::uploadRate() const {
	return m_uploadRate;
}

void GlobalTransferInfo::update() {
	QNetworkRequest request(urlWithPath("/query/transferInfo"));
	QNetworkReply*	reply = m_networkAccessManager->get(request);
	connect(reply, &QNetworkReply::finished, [=] () {
		if((reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 200)) {
			QJsonDocument	jsonDocument	= QJsonDocument::fromJson(reply->readAll());
			QJsonObject		jsonObject		= jsonDocument.object();
			setDownloadRate(jsonObject["dl_info_speed"].toInt());
			setDownloadedBytes(jsonObject["dl_info_data"].toInt());
			setUploadRate(jsonObject["up_info_speed"].toInt());
			setUploadedBytes(jsonObject["up_info_data"].toInt());
			transferSpeedChanged();
		}
	});
}

QUrl GlobalTransferInfo::urlWithPath(const QString &path) {
	return QUrl(settings.value("url").toString() + path);
}

void GlobalTransferInfo::setUploadRate(const quint64 &uploadRate) {
	m_uploadRate = uploadRate;
	emit uploadRateChanged();
}

void GlobalTransferInfo::setDownloadRate(const quint64 &downloadRate)  {
	m_downloadRate = downloadRate;
	emit downloadRateChanged();
}

void GlobalTransferInfo::setUploadedBytes(const quint64 &uploadedBytes) {
	m_uploadedBytes = uploadedBytes;
	emit uploadedBytesChanged();
}

void GlobalTransferInfo::setDownloadedBytes(const quint64 &downloadedBytes) {
	m_downloadedBytes = downloadedBytes;
	emit downloadedBytesChanged();
}

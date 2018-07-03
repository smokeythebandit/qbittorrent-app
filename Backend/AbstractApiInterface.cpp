#include "AbstractApiInterface.h"

AbstractApiInterface::AbstractApiInterface(QNetworkAccessManager *networkAccessManager, QObject *parent) : QObject(parent),
	m_networkAccessManager(networkAccessManager)
{
	connect(&m_updateTimer, &QTimer::timeout, this, &AbstractApiInterface::update);
}

QUrl AbstractApiInterface::url() const {
	return m_settings.value("url").toUrl();
}

void AbstractApiInterface::setUrl(const QUrl &value) {
	m_settings.setValue("url", value);
    emit urlChanged();
}

QString AbstractApiInterface::valueToDataSize(quint64 value) {
    QLocale locale;
    return locale.formattedDataSize(value, 2, QLocale::DataSizeIecFormat);
}

void AbstractApiInterface::get(const QUrl &url, const std::function<void (QNetworkReply *)> callback) {
	QNetworkReply*	reply = m_networkAccessManager->get(QNetworkRequest(url));
	connect(reply, &QNetworkReply::finished, [=] () {
		callback(reply);
        reply->deleteLater();
	});
	connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), [=](QNetworkReply::NetworkError code) {
		Q_UNUSED(code)
		qWarning() << "Connection error during GET on" << url << reply->errorString();
		callback(reply);
        reply->deleteLater();
	});
}

void AbstractApiInterface::post(const QUrl &url, const QByteArray &postdata, const std::function<void (QNetworkReply *)> callback) {
	QNetworkReply*	reply = m_networkAccessManager->post(QNetworkRequest(url), postdata);
	connect(reply, &QNetworkReply::finished, [=] () {
		if(callback) callback(reply);
        delete reply;
	});
	connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), [=](QNetworkReply::NetworkError code) {
		Q_UNUSED(code)
		qWarning() << "Connection error during POST on" << url << reply->errorString();
		if(callback) callback(reply);
        delete reply;
    });
}

QUrl AbstractApiInterface::urlWithPath(const QString &path) {
	return QUrl(url().toString() + path);
}

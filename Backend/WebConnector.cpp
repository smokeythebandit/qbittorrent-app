#include "WebConnector.h"

WebConnector::WebConnector(QNetworkAccessManager *networkAccessManager, QObject *parent) : QObject(parent),
	m_networkAccessManager(networkAccessManager), m_authenticating(false), m_loggedIn(false) {
	loadCookies();
}

WebConnector::~WebConnector() {
	saveCookies();
}

void WebConnector::attemptLogin() {
	qDebug() << "Attempting to login to qBittorrent web API";
	setAuthenticating(true);
//	checkSIDCookie([=] (bool valid) {
//		if(valid) {
//			qDebug() << "Authenticated using SID cookie";
//			setLoggedIn(true);
//		}
//		else {
//			checkCredentials([=] (bool valid) {
//				if(valid) {
//					qDebug() << "Authenticated using stored credentials";
//					setLoggedIn(true);
//				} else {
//					qDebug() << "Failed to login";

//					setLoggedIn(false);
//					setAuthenticating(false);
//				}
//			});
//		}
//	});
	checkCredentials([=] (bool valid) {
		if(valid) {
			qDebug() << "Authenticated using stored credentials";
			setLoggedIn(true);
		} else {
			qDebug() << "Failed to login";
			setLoggedIn(false);
			setAuthenticating(false);
		}
	});
}

bool WebConnector::loggedIn() const {
	return m_loggedIn;
}

QUrl WebConnector::url() const {
	return settings.value("url").toUrl();
}

void WebConnector::setUrl(const QUrl &value) {
	settings.setValue("url", value);
	emit urlChanged();
}

void WebConnector::checkSIDCookie(std::function<void (bool)> callback) {
	//Check if there is an SID cookie
	bool hasSIDCookie = false;
	QList<QNetworkCookie> cookies = m_networkAccessManager->cookieJar()->cookiesForUrl(url());
	foreach(const QNetworkCookie &cookie, cookies) {
		hasSIDCookie |= (cookie.name() == "SID");
	}
	//Check if SID cookie is valid
	if(!hasSIDCookie) {
		qDebug() << "There was no SID cookie";
		callback(false);
	} else {
		QNetworkRequest request(urlWithPath("/api/v2/auth/login"));
		QNetworkReply*	reply = m_networkAccessManager->get(request);
		connect(reply, &QNetworkReply::finished, [=] () {
			if((reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 200)) {
				if(reply->readAll() == "Ok.") {if (callback) callback(true);}
				else {if (callback) callback(true);}
			} else if (callback) callback(false);
		});
		connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
			[=](QNetworkReply::NetworkError code){
			callback(false);
		});
	}
}

void WebConnector::checkCredentials(std::function<void (bool)> callback){
	//Check if there is are credentials
	bool hasCredentials = !username().isEmpty() && !password().isEmpty();
	//Check if credentials are valid
	if(!hasCredentials) callback(false);

	else {
		QUrlQuery query;
		query.addQueryItem("username", username());
		query.addQueryItem("password", password());
		QUrl url (urlWithPath("/api/v2/auth/login?" + query.query()));
		QNetworkRequest request(url);
		QNetworkReply*	reply = m_networkAccessManager->get(request);
		connect(reply, &QNetworkReply::finished, [=] () {
			if((reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 200)) {
				if(reply->readAll() == "Ok.") if (callback) callback(true);
				else callback(false);
			} else if (callback) callback(false);
		});
	}
}

void WebConnector::saveCookies() {
	QList<QNetworkCookie> cookies = m_networkAccessManager->cookieJar()->cookiesForUrl(url());
	QSettings settings;
	settings.beginGroup(QLatin1String("cookies"));
	settings.setValue("cookies", cookies[0].toRawForm());
}

void WebConnector::loadCookies() {
	QSettings settings;
	settings.beginGroup(QLatin1String("cookies"));
	QList<QNetworkCookie> savedCookies = QNetworkCookie::parseCookies(settings.value("cookies").toByteArray());
	foreach (QNetworkCookie cookie, savedCookies) {
		m_networkAccessManager->cookieJar()->insertCookie(cookie);
	}
}

QUrl WebConnector::urlWithPath(const QString &path) {
	return QUrl(url().toString() + path);
}

void WebConnector::setLoggedIn(bool loggedIn) {
	if(loggedIn) setAuthenticating(false);
	m_loggedIn = loggedIn;
	emit loggedInChanged();
}

bool WebConnector::isAuthenticating() const {
	return m_authenticating;
}

void WebConnector::setAuthenticating(bool authenticating) {
	m_authenticating = authenticating;
	emit authenticatingChanged();
}

QString WebConnector::password() const {
	return settings.value("password").toString();;
}

void WebConnector::setPassword(const QString &password) {
	settings.setValue("password", password);
	emit passwordChanged();
}

QString WebConnector::username() const {
	return settings.value("username").toString();
}

void WebConnector::setUsername(const QString &username) {
	settings.setValue("username", username);
	emit usernameChanged();
}


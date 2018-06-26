#include "WebConnector.h"

WebConnector::WebConnector(QNetworkAccessManager *networkAccessManager, QObject *parent) : AbstractApiInterface (networkAccessManager, parent) {
	loadCookies();
}

WebConnector::~WebConnector() {
	saveCookies();
}

void WebConnector::attemptLogin() {
	qDebug() << "Attempting to login to qBittorrent web API";
	setAuthenticating(true);
	checkSIDCookie([=] (bool valid) {
		if(valid) {
			qDebug() << "Authenticated using SID cookie";
			setLoggedIn(true);
		} else {
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
	});
}

void WebConnector::update()
{

}

bool WebConnector::loggedIn() const {
	return m_loggedIn;
}

void WebConnector::checkSIDCookie(std::function<void (bool)> callback) {
	//Check if there is an SID cookie
	qDebug() << "Checking for stored SID cookie";
	bool hasSIDCookie = false;
	QList<QNetworkCookie> cookies = m_networkAccessManager->cookieJar()->cookiesForUrl(url());
	foreach(const QNetworkCookie &cookie, cookies) {
		hasSIDCookie |= (cookie.name() == "SID");
	}

	//Check if SID cookie is valid
	if(!hasSIDCookie) {
		qWarning() << "There was no stored SID cookie";
		callback(false);
	} else {
		qDebug() << "Found SID cookie, checking validity of SID cookie";
		get(urlWithPath("/api/v2/auth/login"), [=] (QNetworkReply *reply) {
			if((reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 200)) {
				qInfo() << "SID cookie was valid";
				callback(reply->readAll() == "Ok.");
			} else {
				qWarning() << "SID cookie was invalid";
				callback(false);
			}
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
				callback(reply->readAll() == "Ok.");
			} else callback(false);
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
	return m_settings.value("password").toString();;
}

void WebConnector::setPassword(const QString &password) {
	m_settings.setValue("password", password);
	emit passwordChanged();
}

QString WebConnector::username() const {
	return m_settings.value("username").toString();
}

void WebConnector::setUsername(const QString &username) {
	m_settings.setValue("username", username);
	emit usernameChanged();
}


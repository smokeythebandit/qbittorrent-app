#ifndef WEBCONNECTOR_H
#define WEBCONNECTOR_H

//Qt framework
#include <QUrl>
#include <QDebug>
#include <QObject>
#include <QtNetwork>

//C++ standard library
#include <functional>

//Internal headers
#include "../AbstractApiInterface.h"

class WebConnector : public AbstractApiInterface
{
		Q_OBJECT
	public:
		Q_PROPERTY(bool loggedIn READ loggedIn NOTIFY loggedInChanged)
		Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
		Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
		Q_PROPERTY(bool authenticating READ isAuthenticating WRITE setAuthenticating NOTIFY authenticatingChanged)
		WebConnector(QNetworkAccessManager *networkAccessManager, QObject *parent = nullptr);
		~WebConnector();

		/**
		 * @brief loggedIn Returns if the user is logged in to qBittorrent
		 * @details checks if there is and SID cookie, and if it is there, verfifies that it is a valid SID cookie
		 * @return returns true if the user is logged in
		 */
		bool loggedIn() const;

		QString username() const;
		void setUsername(const QString &username);

		QString password() const;
		void setPassword(const QString &password);

		bool isAuthenticating() const;
		void setAuthenticating(bool authenticating);

	public slots:
		/**
		 * @brief attemptLogin Tries to login to the qBittorrent applicatio
		 * @details tries loggin in with a cookie or credentials (if any of those are stored)
		 */
		void attemptLogin();

	protected slots:
		void update();

	protected:
		void setLoggedIn(bool loggedIn);
		void checkSIDCookie(std::function<void(bool)> callback);
		void checkCredentials(std::function<void(bool)> callback);
		void saveCookies();
		void loadCookies();

	signals:
		void loggedInChanged();
		void usernameChanged();
		void passwordChanged();
		void authenticatingChanged();

	private:
		bool m_loggedIn;	///< Contains the login status
		bool m_authenticating;
};

#endif // WEBCONNECTOR_H

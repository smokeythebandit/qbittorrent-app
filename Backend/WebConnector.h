#ifndef WEBCONNECTOR_H
#define WEBCONNECTOR_H

//Qt framework
#include <QUrl>
#include <QDebug>
#include <QObject>
#include <QtNetwork>

//C++ standard library
#include <functional>

class WebConnector : public QObject
{
		Q_OBJECT
	public:
		Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
		Q_PROPERTY(bool loggedIn READ loggedIn NOTIFY loggedInChanged)
		Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
		Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
		Q_PROPERTY(bool authenticating READ isAuthenticating WRITE setAuthenticating NOTIFY authenticatingChanged)

		explicit WebConnector(QNetworkAccessManager* m_networkAccessManager, QObject *parent = nullptr);
		~WebConnector();

		/**
		 * @brief loggedIn Returns if the user is logged in to qBittorrent
		 * @details checks if there is and SID cookie, and if it is there, verfifies that it is a valid SID cookie
		 * @return returns true if the user is logged in
		 */
		bool loggedIn() const;

		/**
		 * @brief rootURl Gets the root URL of the qBittorrent web API
		 * @return the root URL of the qBittorrent web API
		 */
		QUrl url() const;

		/**
		 * @brief setRootURl Changes the root URL of the qBittorrent web API
		 * @param value the root URL of the qBittorrent web API
		 */
		void setUrl(const QUrl &value);

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

	protected:
		void setLoggedIn(bool loggedIn);
		QUrl urlWithPath(const QString &path);
		void checkSIDCookie(std::function<void(bool)> callback = std::function<void(bool)>());
		void checkCredentials(std::function<void(bool)> callback = std::function<void(bool)>());
		void saveCookies();
		void loadCookies();

	signals:
		void urlChanged();
		void loggedInChanged();
		void usernameChanged();
		void passwordChanged();
		void authenticatingChanged();

	private:
		bool m_loggedIn;	///< Contains the login status
		QSettings settings;	///< Contains the settings for the application
		bool m_authenticating;
		QNetworkAccessManager *m_networkAccessManager; ///< Allows the application to send network requests and receive replies.
};

#endif // WEBCONNECTOR_H

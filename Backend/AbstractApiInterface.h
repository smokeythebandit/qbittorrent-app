#ifndef ABSTRACTAPIINTERFACE_H
#define ABSTRACTAPIINTERFACE_H

//Qt framework
#include <QObject>
#include <QtNetwork>

//Internal headers
#include "backend_global.h"

//C++ standard library
#include <functional>

class BACKEND_EXPORT AbstractApiInterface : public QObject
{
		Q_OBJECT
	public:
		Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
		AbstractApiInterface(QNetworkAccessManager *networkAccessManager, QObject *parent = nullptr);

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

	protected slots:
		virtual void get(const QUrl &url, const std::function<void(QNetworkReply *)> callback) final;
		virtual void post(const QUrl &url, const QByteArray &postdata, const std::function<void(QNetworkReply *)> callback = std::function<void(QNetworkReply *)>()) final;

		virtual void update() = 0;
		QUrl urlWithPath(const QString &path);

	signals:
		void urlChanged();

	protected:
		QNetworkAccessManager	*m_networkAccessManager; ///< Allows the application to send network requests and receive replies.
		QTimer					m_updateTimer; ///< Calls update() at set interval
		QSettings				m_settings;	///< Contains the settings for the application
};

#endif // ABSTRACTAPIINTERFACE_H

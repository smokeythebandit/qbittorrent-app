#ifndef GLOBALTRANSFERINFO_H
#define GLOBALTRANSFERINFO_H

//Qt framework
#include <QTimer>
#include <QObject>
#include <QtNetwork>

class GlobalTransferInfo : public QObject
{
		Q_OBJECT
	public:
		Q_PROPERTY(QString transferSpeed READ transferSpeed NOTIFY transferSpeedChanged)
		Q_PROPERTY(quint32 downloadedBytes READ downloadedBytes NOTIFY downloadedBytesChanged)
		Q_PROPERTY(quint32 uploadedBytes READ uploadedBytes NOTIFY uploadedBytesChanged)
		Q_PROPERTY(quint32 downloadRate READ downloadRate NOTIFY downloadRateChanged)
		Q_PROPERTY(quint32 uploadRate READ uploadRate NOTIFY uploadRateChanged)

		explicit GlobalTransferInfo(QNetworkAccessManager* networkAccessManager, QObject *parent = nullptr);

		QString transferSpeed() const;
		quint64 downloadedBytes() const;
		quint64 uploadedBytes() const;
		quint64 downloadRate() const;
		quint64 uploadRate() const;

	private slots:
		void setDownloadedBytes(const quint64 &downloadedBytes);
		void setUploadedBytes(const quint64 &uploadedBytes);
		void setDownloadRate(const quint64 &downloadRate);
		void setUploadRate(const quint64 &uploadRate);

	public slots:
		void update();

	protected:
		QUrl urlWithPath(const QString &path);

	signals:
		void downloadedBytesChanged();
		void uploadedBytesChanged();
		void transferSpeedChanged();
		void downloadRateChanged();
		void uploadRateChanged();

	private:
		QNetworkAccessManager *m_networkAccessManager; ///< Allows the application to send network requests and receive replies.
		QSettings settings;	///< Contains the settings for the application
		quint64 m_downloadedBytes;
		quint64 m_uploadedBytes;
		quint64 m_downloadRate;
		quint64 m_uploadRate;
		QTimer  m_updateTimer;

};

#endif // GLOBALTRANSFERINFO_H

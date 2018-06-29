#ifndef GLOBALTRANSFERINFO_H
#define GLOBALTRANSFERINFO_H

//Qt framework
#include <QTimer>
#include <QObject>

//Internal headers
#include "../backend_global.h"
#include "../AbstractApiInterface.h"

class BACKEND_EXPORT GlobalTransferInfo : public AbstractApiInterface
{
		Q_OBJECT
	public:
		Q_PROPERTY(QString transferSpeed READ transferSpeed NOTIFY transferSpeedChanged)
		Q_PROPERTY(quint32 downloadedBytes READ downloadedBytes NOTIFY downloadedBytesChanged)
		Q_PROPERTY(quint32 uploadedBytes READ uploadedBytes NOTIFY uploadedBytesChanged)
		Q_PROPERTY(quint32 downloadRate READ downloadRate NOTIFY downloadRateChanged)
		Q_PROPERTY(quint32 uploadRate READ uploadRate NOTIFY uploadRateChanged)

		GlobalTransferInfo(QNetworkAccessManager *networkAccessManager, QObject *parent = nullptr);

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

	signals:
		void downloadedBytesChanged();
		void uploadedBytesChanged();
		void transferSpeedChanged();
		void downloadRateChanged();
		void uploadRateChanged();

	private:
		quint64 m_downloadedBytes;
		quint64 m_uploadedBytes;
		quint64 m_downloadRate;
		quint64 m_uploadRate;

};

#endif // GLOBALTRANSFERINFO_H

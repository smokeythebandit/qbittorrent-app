#ifndef TORRENT_H
#define TORRENT_H

//Qt framework
#include <QObject>

//Internal headers
#include "../backend_global.h"
#include "../AbstractApiInterface.h"

class BACKEND_EXPORT Torrent : public AbstractApiInterface
{
    Q_OBJECT
public:
    Q_PROPERTY(QString hash READ hash)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(quint64 size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(float   progress READ progress WRITE setProgress NOTIFY progressChanged)
    Q_PROPERTY(quint64 downloadSpeed READ downloadSpeed WRITE setDownloadSpeed NOTIFY downloadSpeedChanged)
    Q_PROPERTY(quint64 uploadSpeed READ uploadSpeed WRITE setUploadSpeed NOTIFY uploadSpeedChanged)
    Q_PROPERTY(quint64 priority READ priority WRITE setPriority NOTIFY priorityChanged)
    Q_PROPERTY(quint64 numberConnectedSeeds READ numberConnectedSeeds WRITE setNumberConnectedSeeds NOTIFY numberConnectedSeedsChanged)
    Q_PROPERTY(quint64 numberCompletedSeeds READ numberCompletedSeeds WRITE setNumberCompletedSeeds NOTIFY numberCompletedSeedsChanged)
    Q_PROPERTY(quint64 numberLeechers READ numberLeechers WRITE setNumberLeechers NOTIFY numberLeechersChanged)
    Q_PROPERTY(quint64 numberIncompletedSeeds READ numberIncompletedSeeds WRITE setNumberIncompletedSeeds NOTIFY numberIncompletedSeedsChanged)
    Q_PROPERTY(float   ratio READ ratio WRITE setRatio NOTIFY ratioChanged)
    Q_PROPERTY(quint64 eta READ eta WRITE setEta NOTIFY etaChanged)
    Q_PROPERTY(QString state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(bool    sequentialDownload READ sequentialDownload WRITE setSequentialDownload NOTIFY sequentialDownloadChanged)
    Q_PROPERTY(bool    lastPiecePriority READ lastPiecePriority WRITE setLastPiecePriority NOTIFY lastPiecePriorityChanged)
    Q_PROPERTY(QString category READ category WRITE setCategory NOTIFY categoryChanged)
    Q_PROPERTY(bool    superSeeding READ superSeeding WRITE setSuperSeeding NOTIFY superSeedingChanged)
    Q_PROPERTY(bool    forceStart READ forceStart WRITE setForceStart NOTIFY forceStartChanged)
    Torrent(QString hash, QNetworkAccessManager *networkAccessManager, QObject *parent = nullptr);

    QString hash() const;

    QString name() const;
    void setName(const QString &name);

    quint64 size() const;
    void setSize(const quint64 &size);

    float progress() const;
    void setProgress(float progress);

    quint64 downloadSpeed() const;
    void setDownloadSpeed(const quint64 &downloadSpeed);

    quint64 uploadSpeed() const;
    void setUploadSpeed(const quint64 &uploadSpeed);

    quint64 priority() const;
    void setPriority(const quint64 &priority);

    quint64 numberConnectedSeeds() const;
    void setNumberConnectedSeeds(const quint64 &numberConnectedSeeds);

    quint64 numberCompletedSeeds() const;
    void setNumberCompletedSeeds(const quint64 &numberCompletedSeeds);

    quint64 numberLeechers() const;
    void setNumberLeechers(const quint64 &numberLeechers);

    quint64 numberIncompletedSeeds() const;
    void setNumberIncompletedSeeds(const quint64 &numberIncompletedSeeds);

    float ratio() const;
    void setRatio(float ratio);

    quint64 eta() const;
    void setEta(const quint64 &eta);

    QString state() const;
    void setState(const QString &state);

    bool sequentialDownload() const;
    void setSequentialDownload(bool sequentialDownload);

    bool lastPiecePriority() const;
    void setLastPiecePriority(bool lastPiecePriority);

    QString category() const;
    void setCategory(const QString &category);

    bool superSeeding() const;
    void setSuperSeeding(bool superSeeding);

    bool forceStart() const;
    void setForceStart(bool forceStart);

signals:
    void    nameChanged();
    void    sizeChanged();
    void    progressChanged();
    void    downloadSpeedChanged();
    void    uploadSpeedChanged();
    void    priorityChanged();
    void    numberConnectedSeedsChanged();
    void    numberCompletedSeedsChanged();
    void    numberLeechersChanged();
    void    numberIncompletedSeedsChanged();
    void    ratioChanged();
    void    etaChanged();
    void    stateChanged();
    void    sequentialDownloadChanged();
    void    lastPiecePriorityChanged();
    void    categoryChanged();
    void    superSeedingChanged();
    void    forceStartChanged();

protected slots:
    virtual void update();

private:
    QString m_hash;
    QString m_name;
    quint64 m_size;
    float   m_progress;
    quint64 m_downloadSpeed;
    quint64 m_uploadSpeed;
    quint64 m_priority;
    quint64 m_numberConnectedSeeds;
    quint64 m_numberCompletedSeeds;
    quint64 m_numberLeechers;
    quint64 m_numberIncompletedSeeds;
    float   m_ratio;
    quint64 m_eta;
    QString m_state;
    bool    m_sequentialDownload;
    bool    m_lastPiecePriority;
    QString m_category;
    bool    m_superSeeding;
    bool    m_forceStart;
};

#endif // TORRENT_H

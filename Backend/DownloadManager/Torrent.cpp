#include "Torrent.h"

Torrent::Torrent(QString hash, QNetworkAccessManager *networkAccessManager, QObject *parent) : AbstractApiInterface(networkAccessManager, parent), m_hash(hash)
{

}

QString Torrent::hash() const {
    return m_hash;
}

QString Torrent::name() const {
    return m_name;
}

void Torrent::setName(const QString &name) {
    m_name = name;
    emit nameChanged();
}

quint64 Torrent::size() const {
    return m_size;
}

void Torrent::setSize(const quint64 &size) {
    m_size = size;
    emit sizeChanged();
}

float Torrent::progress() const {
    return m_progress;
}

void Torrent::setProgress(float progress) {
    m_progress = progress;
    emit progressChanged();
}

quint64 Torrent::downloadSpeed() const {
    return m_downloadSpeed;
}

void Torrent::setDownloadSpeed(const quint64 &downloadSpeed) {
    m_downloadSpeed = downloadSpeed;
    emit downloadSpeedChanged();
}

quint64 Torrent::uploadSpeed() const {
    return m_uploadSpeed;
}

void Torrent::setUploadSpeed(const quint64 &uploadSpeed) {
    m_uploadSpeed = uploadSpeed;
    emit uploadSpeedChanged();
}

quint64 Torrent::priority() const
{
    return m_priority;
}

void Torrent::setPriority(const quint64 &priority) {
    m_priority = priority;
    emit priorityChanged();
}

quint64 Torrent::numberConnectedSeeds() const {
    return m_numberConnectedSeeds;
}

void Torrent::setNumberConnectedSeeds(const quint64 &numberConnectedSeeds) {
    m_numberConnectedSeeds = numberConnectedSeeds;
    emit numberConnectedSeedsChanged();
}

quint64 Torrent::numberCompletedSeeds() const {
    return m_numberCompletedSeeds;
}

void Torrent::setNumberCompletedSeeds(const quint64 &numberCompletedSeeds) {
    m_numberCompletedSeeds = numberCompletedSeeds;
    emit numberCompletedSeedsChanged();
}

quint64 Torrent::numberLeechers() const {
    return m_numberLeechers;
}

void Torrent::setNumberLeechers(const quint64 &numberLeechers) {
    m_numberLeechers = numberLeechers;
    emit numberLeechersChanged();
}

quint64 Torrent::numberIncompletedSeeds() const {
    return m_numberIncompletedSeeds;
}

void Torrent::setNumberIncompletedSeeds(const quint64 &numberIncompletedSeeds) {
    m_numberIncompletedSeeds = numberIncompletedSeeds;
    emit numberIncompletedSeedsChanged();
}

float Torrent::ratio() const {
    return m_ratio;
}

void Torrent::setRatio(float ratio) {
    m_ratio = ratio;
    emit ratioChanged();
}

quint64 Torrent::eta() const {
    return m_eta;
}

void Torrent::setEta(const quint64 &eta) {
    m_eta = eta;
    emit etaChanged();
}

QString Torrent::state() const {
    return m_state;
}

void Torrent::setState(const QString &state) {
    m_state = state;
    emit stateChanged();
}

bool Torrent::sequentialDownload() const {
    return m_sequentialDownload;
}

void Torrent::setSequentialDownload(bool sequentialDownload) {
    m_sequentialDownload = sequentialDownload;
    emit sequentialDownloadChanged();
}

bool Torrent::lastPiecePriority() const {
    return m_lastPiecePriority;
}

void Torrent::setLastPiecePriority(bool lastPiecePriority) {
    m_lastPiecePriority = lastPiecePriority;
    emit lastPiecePriorityChanged();
}

QString Torrent::category() const {
    return m_category;
}

void Torrent::setCategory(const QString &category) {
    m_category = category;
    emit categoryChanged();;
}

bool Torrent::superSeeding() const {
    return m_superSeeding;
}

void Torrent::setSuperSeeding(bool superSeeding) {
    m_superSeeding = superSeeding;
    emit superSeedingChanged();
}

bool Torrent::forceStart() const {
    return m_forceStart;
}

void Torrent::setForceStart(bool forceStart) {
    m_forceStart = forceStart;
    emit forceStartChanged();
}

void Torrent::update()
{

}

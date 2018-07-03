QT += qml quick network

TARGET = Backend
TEMPLATE = lib

DEFINES += BACKEND_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GlobalTransferInfo/GlobalTransferInfo.cpp \
    WebConnector/WebConnector.cpp \
    AbstractApiInterface.cpp \
    Backend.cpp \
    DebugMessageHandler.cpp \
    DownloadManager/Categorie.cpp \
    DownloadManager/Torrent.cpp \
    DownloadManager/DownloadManager.cpp


HEADERS += \
    GlobalTransferInfo/GlobalTransferInfo.h \
    WebConnector/WebConnector.h \
    AbstractApiInterface.h \
    Backend.h \
    backend_global.h \
    DebugMessageHandler.h \
    DownloadManager/Categorie.h \
    DownloadManager/Torrent.h \
    DownloadManager/DownloadManager.h


SUBDIRS += \
    Backend.pro

DISTFILES += \
    Backend.pri

include(../Libraries/QObjectListModel/de_skycoder42_qobjectlistmodel.pri)

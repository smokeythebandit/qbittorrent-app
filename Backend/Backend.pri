#Backend
win32:CONFIG(release, debug|release): LIBS += -L$$shadowed($$PWD)\release -lBackend
else:win32:CONFIG(debug, debug|release): LIBS += -L$$shadowed($$PWD)\debug -lBackend
else:unix: LIBS += -L$$shadowed($$PWD) -lBackend

INCLUDEPATH += $$PWD

include(../Libraries/QObjectListModel/de_skycoder42_qobjectlistmodel.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS  = -L/usr/lib -I/usr/include/mysql -rdynamic -L/usr/lib/mysql -lmysqlclient -lsqlite3 -lsqlite -lpthread
INCLUDEPATH += /usr/include/mysql

SOURCES += main.cpp \
    server.cpp \
    proto.cpp \
    objetvar.cpp \
    md5.cpp \
    Timer.cpp \
    funcCMD.cpp \
    func.cpp \
    database.cpp \
    client.cpp

HEADERS += \
    md5.h \
    you.h \
    TitreInclude.h \
    TitreCmd.h \
    client.h


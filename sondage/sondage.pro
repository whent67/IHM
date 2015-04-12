#-------------------------------------------------
#
# Project created by QtCreator 2015-03-19T14:48:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sondage
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ajoutpersonne.cpp \
    aubonlait.cpp \
    chargement.cpp \
    gestionsondes.cpp

HEADERS  += mainwindow.h \
    ajoutpersonne.h \
    aubonlait.h \
    chargement.h \
    gestionsondes.h \
    personne.h \
    sondage.h

FORMS    += mainwindow.ui \
    ajoutpersonne.ui \
    aubonlait.ui \
    chargement.ui \
    gestionsondes.ui

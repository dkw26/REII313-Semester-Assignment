#-------------------------------------------------
#
# Project created by QtCreator 2020-06-07T19:18:41
#
#-------------------------------------------------

QT       += core gui

TARGET = SemesterProjectGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    methodsdialog.cpp \
    simplexproblem.cpp \
    bnbproblem.cpp

HEADERS  += mainwindow.h \
    methodsdialog.h \
    simplexproblem.h \
    bnbproblem.h \
    SimplexSolver.h \
    bnbSolver.h

FORMS    += mainwindow.ui \
    methodsdialog.ui \
    simplexproblem.ui \
    bnbproblem.ui

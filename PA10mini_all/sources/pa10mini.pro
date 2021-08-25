######################################################################
# Automatically generated by qmake (3.1) Tue Aug 24 19:56:43 2021
######################################################################

TEMPLATE = app
TARGET = pa10mini

INCLUDEPATH += .
windows: INCLUDEPATH += C:/Qwt-6.1.4/include
windows: INCLUDEPATH += D:/workspace/github/dlfcn-win32/src

QT += core widgets opengl gui

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
windows: DEFINES += _WINDOWS


include ( C:/Qwt-6.1.4/features/qwt.prf )
LIBS += D:/workspace/github/build-dlfcn-win32-Qt_5_14_1_MinGW_64_bit-Debug/lib/libdl.dll.a

#windows: LIBS += C:/Qwt-6.1.4/lib
#windows: LIBS += -LD:/soft/developerTools/qt/qwt-6.1.4/lib/libqwt.a
CONFIG += qwt
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += circuititem.h \
           circuititemedit.h \
           daesystem.h \
           equaledit.h \
           expression.h \
           FlexLexer.h \
           location.hh \
           parser.hpp \
           pax_prototype.h \
           plot.h \
           plotwindow.h \
           position.hh \
           resource.h \
           scanner.h \
           schemeview.h \
           solver.h \
           solverparam.h \
           stack.hh \
           textdriver.h \
           variablechooser.h \
           manzhuk/manzhuk.h \
           manzhuk/fcttask/fcttask.h \
           /equaledit.h \
           /schemeview.h \
           /plot.h \
           /FlexLexer.h

FORMS += circuititemedit.ui \
         pax_prototype.ui \
         plotwindow.ui \
         solverparam.ui \
         variablechooser.ui

#LEXSOURCES += scanner.l
#YACCSOURCES += parser.y
SOURCES += circuititem.cpp \
           circuititemedit.cpp \
           daesystem.cpp \
           equaledit.cpp \
           expression.cpp \
           main.cpp \
           parser.cpp \
           pax_prototype.cpp \
           plot.cpp \
           plotwindow.cpp \
           scanner.cpp \
           schemeview.cpp \
           solver.cpp \
           solverparam.cpp \
           textdriver.cpp \
           variablechooser.cpp \
           manzhuk/manzhuk.cpp
           #manzhuk/fcttask/fcttask.cpp

RESOURCES += pax_prototype.qrc

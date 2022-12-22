QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DataAnalysisPage/dataanalysiswidget.cpp \
    DataEntryPage/TableContents/coordtablewidget.cpp \
    DataEntryPage/TableContents/customitemdelegate.cpp \
    DataEntryPage/TableContents/dumptablewidget.cpp \
    DataEntryPage/TableContents/pittablewidget.cpp \
    DataEntryPage/TableContents/roadtablewidget.cpp \
    DataEntryPage/customgpixmapitem.cpp \
    DataEntryPage/customgraphicsscene.cpp \
    DataEntryPage/customlistwidget.cpp \
    DataEntryPage/dataentrywidget.cpp \
    DataEntryPage/datapanel.cpp \
    DataEntryPage/dumpoptionwgt.cpp \
    DataEntryPage/graphicalwindow.cpp \
    DataEntryPage/previewwindow.cpp \
    DataEntryPage/summarywindow.cpp \
    DisplayPage/displaywidget.cpp \
    DisplayPage/drawingwidget.cpp \
    DisplayPage/millwgt.cpp \
    DisplayPage/resourcewgt.cpp \
    DisplayPage/stockpilewgt.cpp \
    DisplayPage/tablepropertywindow.cpp \
    ParameterPage/parameterwidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    DataAnalysisPage/dataanalysiswidget.h \
    DataEntryPage/TableContents/coordtablewidget.h \
    DataEntryPage/TableContents/customitemdelegate.h \
    DataEntryPage/TableContents/dumptablewidget.h \
    DataEntryPage/TableContents/pittablewidget.h \
    DataEntryPage/TableContents/roadtablewidget.h \
    DataEntryPage/customgpixmapitem.h \
    DataEntryPage/customgraphicsscene.h \
    DataEntryPage/customlistwidget.h \
    DataEntryPage/dataentrywidget.h \
    DataEntryPage/datapanel.h \
    DataEntryPage/dumpoptionwgt.h \
    DataEntryPage/graphicalwindow.h \
    DataEntryPage/previewwindow.h \
    DataEntryPage/summarywindow.h \
    DisplayPage/displaywidget.h \
    DisplayPage/drawingwidget.h \
    DisplayPage/millwgt.h \
    DisplayPage/resourcewgt.h \
    DisplayPage/stockpilewgt.h \
    DisplayPage/tablepropertywindow.h \
    ParameterPage/parameterwidget.h \
    mainwindow.h

FORMS += \
    DataAnalysisPage/dataanalysiswidget.ui \
    DataEntryPage/dataentrywidget.ui \
    DataEntryPage/datapanel.ui \
    DataEntryPage/dumpoptionwgt.ui \
    DataEntryPage/graphicalwindow.ui \
    DataEntryPage/previewwindow.ui \
    DataEntryPage/summarywindow.ui \
    DisplayPage/displaywidget.ui \
    DisplayPage/drawingwidget.ui \
    DisplayPage/millwgt.ui \
    DisplayPage/resourcewgt.ui \
    DisplayPage/stockpilewgt.ui \
    DisplayPage/tablepropertywindow.ui \
    ParameterPage/parameterwidget.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

win32:RC_ICONS += MineOpt.ico
VERSION = 1.0.21
TARGET = MineOpt

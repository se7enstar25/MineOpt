#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include "DataEntryPage/dataentrywidget.h"
#include "DataAnalysisPage/dataanalysiswidget.h"
#include "DisplayPage/displaywidget.h"
#include "ParameterPage/parameterwidget.h"
#include "DataEntryPage/graphicalwindow.h"
#include "DisplayPage/drawingwidget.h"
#include <QActionGroup>
#include <QDomDocument>
#include <QDomElement>
#include <QMessageBox>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private slots:
    void pageChanged(QAction *a);

    void on_actionExit_triggered();

    void on_action_Open_triggered();

    void on_action_Save_triggered();

    void on_actionSave_As_triggered();

private:
    Ui::MainWindow *ui;
    QActionGroup *action_group;
    QAction *btn_display;
    QAction *btn_parameter;
    QAction *btn_data_entry;
    QAction *btn_data_analysis;
    bool isNew{true}, askSave{false};
    QString projectName;
};
#endif // MAINWINDOW_H

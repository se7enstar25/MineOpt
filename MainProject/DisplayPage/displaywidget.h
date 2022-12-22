#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>
#include <QSplitter>
#include <QVBoxLayout>
#include "../DataEntryPage/graphicalwindow.h"
#include "drawingwidget.h"
#include "tablepropertywindow.h"

namespace Ui {
class DisplayWidget;
}

class DisplayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayWidget(QWidget *parent = nullptr);
    static DisplayWidget* instance();
    int getYear();
    void setYear(int year);
    void saveStockPileYearsModel(QString path);
    void saveStockPileCoordsModel(QString path);
    void loadStockPileYearsModel(QString path);
    void loadStockPileCoordsModel(QString path);
    void saveMillMinYearsModel(QString path);
    void saveMillMaxYearsModel(QString path);
    void saveMillCoordsModel(QString path);
    void loadMillMinYearsModel(QString path);
    void loadMillMaxYearsModel(QString path);
    void loadMillCoordsModel(QString path);
    void saveResourceModel(QString path);
    void loadResourceModel(QString path);
    ~DisplayWidget();

public:
    QVBoxLayout *layout, *cp_layout, *rp_layout;
    QSplitter *splitter;
    QFrame *center_pane, *right_pane;

private:
    Ui::DisplayWidget *ui;
};

#endif // DISPLAYWIDGET_H

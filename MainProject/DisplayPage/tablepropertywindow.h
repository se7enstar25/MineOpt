#ifndef TABLEPROPERTYWINDOW_H
#define TABLEPROPERTYWINDOW_H

#include <QWidget>
#include <QActionGroup>
#include "resourcewgt.h"
#include "stockpilewgt.h"
#include "millwgt.h"

namespace Ui {
class TablePropertyWindow;
}

class TablePropertyWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TablePropertyWindow(QWidget *parent = nullptr);
    static TablePropertyWindow* instance();
    ~TablePropertyWindow();

public slots:
    void onYearChanged(int year);

    void pageChanged(QAction *a);

private:
    Ui::TablePropertyWindow *ui;
    QActionGroup *action_group;
    QAction *btn_stock;
    QAction *btn_mill;
    QAction *btn_resource;

};

#endif // TABLEPROPERTYWINDOW_H

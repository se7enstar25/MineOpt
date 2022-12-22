#ifndef PREVIEWWINDOW_H
#define PREVIEWWINDOW_H

#include <QWidget>
#include <QActionGroup>
#include <QStandardItemModel>
#include <QItemDelegate>
#include <QHeaderView>
#include "datapanel.h"
#include "TableContents/coordtablewidget.h"
#include "TableContents/dumptablewidget.h"
#include "TableContents/pittablewidget.h"
#include "TableContents/roadtablewidget.h"

namespace Ui {
class PreviewWindow;
}

class PreviewWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PreviewWindow(QWidget *parent = nullptr);
    ~PreviewWindow();

public slots:
    void onCurDataChanged(CSVTYPE type, QString fileName);
    void tableChanged(QAction *a);

private slots:
    void on_btn_add_clicked();

    void on_btn_remove_clicked();

private:
    Ui::PreviewWindow *ui;
    QActionGroup *action_group;
    QAction *btn_pit, *btn_roads, *btn_coordinates, *btn_dumps;
    CoordTableWidget *coord_table_wgt;
    RoadTableWidget *road_table_wgt;
    DumpTableWidget *dump_table_wgt;
    PitTableWidget *pit_table_wgt;
    QTableView *cur_table;
};

#endif // PREVIEWWINDOW_H

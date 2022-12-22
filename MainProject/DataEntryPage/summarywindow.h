#ifndef SUMMARYWINDOW_H
#define SUMMARYWINDOW_H

#include <QWidget>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include "datapanel.h"
#include <QTextStream>
#include <QMap>

namespace Ui {
class SummaryWindow;
}

struct Summary{
    QString name;
    double tot;
    double twv;
    double tv;
};

class SummaryWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SummaryWindow(QWidget *parent = nullptr);
    static SummaryWindow* instance();
    ~SummaryWindow();

public slots:
    void onCurDataChanged(CSVTYPE type, QString fileName);

signals:
    void pitDumpCntChanged(int pit_cnt, int dump_cnt);

private:
    Ui::SummaryWindow *ui;
    QList<Summary> dump_list, pit_list;
    Summary total_pit, total_dump;
    bool pit_loaded = false;
    bool dump_loaded = false;
    bool coord_loaded = false;
    bool road_loaded = false;
    QMap<QString, double> dump_hash;
    QMap<QString, Summary> sum_pit_hash;
    QMap<QString, QString> pit_hash;
};

#endif // SUMMARYWINDOW_H

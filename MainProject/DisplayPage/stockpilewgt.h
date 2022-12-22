#ifndef STOCKPILEWGT_H
#define STOCKPILEWGT_H

#include <QWidget>
#include <QStandardItemModel>
#include <QFile>
#include "../DataEntryPage/customgraphicsscene.h"

namespace Ui {
class StockPileWgt;
}

class StockPileWgt : public QWidget
{
    Q_OBJECT

public:
    explicit StockPileWgt(QWidget *parent = nullptr);
    ~StockPileWgt();
    static StockPileWgt* instance();

public slots:
    void setYear(int year);
    void onStockAdded();
    void onStockRemoved();
    void onDataChanged(const QModelIndex&, const QModelIndex&);
    void saveYearModel(QString path);
    void saveCoordModel(QString path);
    void loadYearModel(QString path);
    void loadCoordModel(QString path);
private:
    Ui::StockPileWgt *ui;
    QStandardItemModel *year_model, *coord_model;
    int year;
    int stock_cnt;
};

#endif // STOCKPILEWGT_H

#ifndef MILLWGT_H
#define MILLWGT_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QStandardItemModel>

namespace Ui {
class MillWgt;
}

class MillWgt : public QWidget
{
    Q_OBJECT

public:
    explicit MillWgt(QWidget *parent = nullptr);
    ~MillWgt();
    static MillWgt* instance();

public slots:
    void setYear(int year);
    void onMillAdded();
    void onMillRemoved();
    void onMaxDataChanged(const QModelIndex& tl, const QModelIndex& br);
    void onMinDataChanged(const QModelIndex& tl, const QModelIndex& br);
    void saveMinYearModel(QString path);
    void saveMaxYearModel(QString path);
    void saveCoordModel(QString path);
    void loadMinYearModel(QString path);
    void loadMaxYearModel(QString path);
    void loadCoordModel(QString path);

private:
    Ui::MillWgt *ui;
    QStandardItemModel *min_year_model, *max_year_model, *coord_model;
    int year{1};
    int mill_cnt;
};

#endif // MILLWGT_H

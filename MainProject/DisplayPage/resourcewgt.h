#ifndef RESOURCEWGT_H
#define RESOURCEWGT_H

#include <QWidget>
#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>

namespace Ui {
class ResourceWgt;
}

class ResourceWgt : public QWidget
{
    Q_OBJECT

public:
    explicit ResourceWgt(QWidget *parent = nullptr);
    ~ResourceWgt();
    static ResourceWgt* instance();

public slots:
    void setYear(int year);
    void onDataChanged(const QModelIndex&, const QModelIndex&);
    void saveResourceModel(QString path);
    void loadResourceModel(QString path);

private:
    Ui::ResourceWgt *ui;
    int year;
    QStandardItemModel *resource_model;
};

#endif // RESOURCEWGT_H

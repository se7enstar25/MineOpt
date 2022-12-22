#ifndef PARAMETERWIDGET_H
#define PARAMETERWIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QFile>

namespace Ui {
class ParameterWidget;
}

class ParameterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ParameterWidget(QWidget *parent = nullptr);
    static ParameterWidget* instance();
    ~ParameterWidget();

public slots:
    void onYearChanged(int year);
    void onDataChanged(const QModelIndex&, const QModelIndex&);
    void saveModel(QString path);
    void loadModel(QString path);
private:
    Ui::ParameterWidget *ui;
    int year;
    QStandardItemModel *model;
};

#endif // PARAMETERWIDGET_H

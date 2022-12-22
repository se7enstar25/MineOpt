#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include <QWidget>
#include "../DataEntryPage/graphicalwindow.h"

namespace Ui {
class DrawingWidget;
}

class DrawingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DrawingWidget(QWidget *parent = nullptr);
    static DrawingWidget* instance();
    int getYear();
    void setYear(int year);
    ~DrawingWidget();

private slots:
    void on_btn_add_stock_clicked();

    void on_btn_add_mill_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_btn_remove_stock_clicked();

    void on_btn_remove_mill_clicked();

signals:
    void yearChanged(int year);

private:
    Ui::DrawingWidget *ui;
};

#endif // DRAWINGWIDGET_H

#ifndef DATAANALYSISWIDGET_H
#define DATAANALYSISWIDGET_H

#include <QWidget>

namespace Ui {
class DataAnalysisWidget;
}

class DataAnalysisWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DataAnalysisWidget(QWidget *parent = nullptr);
    static DataAnalysisWidget* instance();
    ~DataAnalysisWidget();

private:
    Ui::DataAnalysisWidget *ui;
};

#endif // DATAANALYSISWIDGET_H

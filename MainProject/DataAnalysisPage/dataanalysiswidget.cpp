#include "dataanalysiswidget.h"
#include "ui_dataanalysiswidget.h"

DataAnalysisWidget::DataAnalysisWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataAnalysisWidget)
{
    ui->setupUi(this);
}

DataAnalysisWidget *DataAnalysisWidget::instance()
{
    static DataAnalysisWidget *singleton = new DataAnalysisWidget;
    return singleton;
}

DataAnalysisWidget::~DataAnalysisWidget()
{
    delete ui;
}

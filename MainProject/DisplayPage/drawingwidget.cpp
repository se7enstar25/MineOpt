#include "drawingwidget.h"
#include "ui_drawingwidget.h"

DrawingWidget::DrawingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawingWidget)
{
    ui->setupUi(this);
}

DrawingWidget *DrawingWidget::instance()
{
    static DrawingWidget *singleton = new DrawingWidget;
    return singleton;
}

int DrawingWidget::getYear()
{
    return ui->comboBox->currentText().toInt();
}

void DrawingWidget::setYear(int year)
{
    ui->comboBox->setCurrentIndex(year-1);
    emit yearChanged(year);
}

DrawingWidget::~DrawingWidget()
{
    delete ui;
}

void DrawingWidget::on_btn_add_stock_clicked()
{
    GraphicalWindow::instance()->addStock();
}

void DrawingWidget::on_btn_add_mill_clicked()
{
    GraphicalWindow::instance()->addMill();
}

void DrawingWidget::on_comboBox_activated(const QString &arg1)
{
    int cnt_year = arg1.toInt();
    emit yearChanged(cnt_year);
}

void DrawingWidget::on_btn_remove_stock_clicked()
{
    GraphicalWindow::instance()->removeStock();
}

void DrawingWidget::on_btn_remove_mill_clicked()
{
    GraphicalWindow::instance()->removeMill();
}

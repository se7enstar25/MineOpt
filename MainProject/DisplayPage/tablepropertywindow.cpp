#include "tablepropertywindow.h"
#include "ui_tablepropertywindow.h"

TablePropertyWindow::TablePropertyWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TablePropertyWindow)
{
    ui->setupUi(this);
    action_group = new QActionGroup(this);
    btn_stock = new QAction("STOCK PILE");
    btn_mill = new QAction("PROCESS PLANTS");
    btn_resource = new QAction("RESOURCE");
    action_group->addAction(btn_mill);
    action_group->addAction(btn_stock);
    action_group->addAction(btn_resource);
    ui->btn_mill->setDefaultAction(btn_mill);
    ui->btn_stock->setDefaultAction(btn_stock);
    ui->btn_resource->setDefaultAction(btn_resource);
    btn_stock->setCheckable(true);
    btn_stock->setChecked(true);
    btn_mill->setCheckable(true);
    btn_resource->setCheckable(true);

    connect(action_group, &QActionGroup::triggered, this, &TablePropertyWindow::pageChanged);

    ui->stackedWidget->addWidget(StockPileWgt::instance());
    ui->stackedWidget->addWidget(MillWgt::instance());
    ui->stackedWidget->addWidget(ResourceWgt::instance());

    onYearChanged(1);
}

TablePropertyWindow *TablePropertyWindow::instance()
{
    static TablePropertyWindow *singleton = new TablePropertyWindow;
    return singleton;
}

TablePropertyWindow::~TablePropertyWindow()
{
    delete ui;
}

void TablePropertyWindow::onYearChanged(int year)
{
    StockPileWgt::instance()->setYear(year);
    MillWgt::instance()->setYear(year);
    ResourceWgt::instance()->setYear(year);
}

void TablePropertyWindow::pageChanged(QAction *a)
{
    if (a == btn_stock) {
        ui->stackedWidget->setCurrentIndex(0);
    }
    if (a == btn_mill) {
        ui->stackedWidget->setCurrentIndex(1);
    }
    if (a == btn_resource) {
        ui->stackedWidget->setCurrentIndex(2);
    }
}

#include "displaywidget.h"
#include "ui_displaywidget.h"

DisplayWidget::DisplayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayWidget)
{
    ui->setupUi(this);
    center_pane = new QFrame;
    cp_layout = new QVBoxLayout(center_pane);
    cp_layout->addWidget(GraphicalWindow::instance());
    right_pane = new QFrame;
    rp_layout = new QVBoxLayout(right_pane);
    rp_layout->addWidget(TablePropertyWindow::instance());
    layout = new QVBoxLayout(this);
    splitter = new QSplitter;
    splitter->addWidget(DrawingWidget::instance());
    splitter->addWidget(center_pane);
    splitter->addWidget(right_pane);
    splitter->setSizes(QList<int>{100,300,300});
    layout->addWidget(splitter);
    layout->setContentsMargins(0,0,0,0);
    cp_layout->setContentsMargins(0,0,0,0);
    rp_layout->setContentsMargins(0,0,0,0);

    connect(DrawingWidget::instance(), &DrawingWidget::yearChanged, TablePropertyWindow::instance(), &TablePropertyWindow::onYearChanged);
    connect(GraphicalWindow::instance(), &GraphicalWindow::stockAdded, StockPileWgt::instance(), &StockPileWgt::onStockAdded);
    connect(GraphicalWindow::instance(), &GraphicalWindow::stockRemoved, StockPileWgt::instance(), &StockPileWgt::onStockRemoved);
    connect(GraphicalWindow::instance(), &GraphicalWindow::millAdded, MillWgt::instance(), &MillWgt::onMillAdded);
    connect(GraphicalWindow::instance(), &GraphicalWindow::millRemoved, MillWgt::instance(), &MillWgt::onMillRemoved);

}

DisplayWidget *DisplayWidget::instance()
{
    static DisplayWidget *singleton = new DisplayWidget;
    return singleton;
}

int DisplayWidget::getYear()
{
    return DrawingWidget::instance()->getYear();
}

void DisplayWidget::setYear(int year)
{
    DrawingWidget::instance()->setYear(year);
}

void DisplayWidget::saveStockPileYearsModel(QString path)
{
    StockPileWgt::instance()->saveYearModel(path);
}

void DisplayWidget::saveStockPileCoordsModel(QString path)
{
    StockPileWgt::instance()->saveCoordModel(path);
}

void DisplayWidget::loadStockPileYearsModel(QString path)
{
    StockPileWgt::instance()->loadYearModel(path);
}

void DisplayWidget::loadStockPileCoordsModel(QString path)
{
    StockPileWgt::instance()->loadCoordModel(path);
}

void DisplayWidget::saveMillMinYearsModel(QString path)
{
    MillWgt::instance()->saveMinYearModel(path);
}

void DisplayWidget::saveMillMaxYearsModel(QString path)
{
    MillWgt::instance()->saveMaxYearModel(path);
}

void DisplayWidget::saveMillCoordsModel(QString path)
{
    MillWgt::instance()->saveCoordModel(path);
}

void DisplayWidget::loadMillMinYearsModel(QString path)
{
    MillWgt::instance()->loadMinYearModel(path);
}

void DisplayWidget::loadMillMaxYearsModel(QString path)
{
    MillWgt::instance()->loadMaxYearModel(path);
}

void DisplayWidget::loadMillCoordsModel(QString path)
{
    MillWgt::instance()->loadCoordModel(path);
}

void DisplayWidget::saveResourceModel(QString path)
{
    ResourceWgt::instance()->saveResourceModel(path);
}

void DisplayWidget::loadResourceModel(QString path)
{
    ResourceWgt::instance()->loadResourceModel(path);
}

DisplayWidget::~DisplayWidget()
{
    delete ui;
}

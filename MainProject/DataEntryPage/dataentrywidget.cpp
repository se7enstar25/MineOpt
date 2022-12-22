#include "dataentrywidget.h"
#include "ui_dataentrywidget.h"

DataEntryWidget::DataEntryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataEntryWidget)
{
    ui->setupUi(this);

    layout = new QVBoxLayout;

    this->setLayout(layout);
    splitter = new QSplitter(Qt::Horizontal, this);
    left_pane = new QFrame;
    center_pane = new QFrame;
    right_pane = new QFrame;

    splitter->addWidget(left_pane);
    splitter->addWidget(center_pane);
    splitter->addWidget(right_pane);

    splitter->setSizes(QList<int>{100,200,300});
    layout->addWidget(splitter);
    layout->setContentsMargins(0,0,0,0);

    dp_layout = new QVBoxLayout;
    left_pane->setLayout(dp_layout);
    pits_panel = new DataPanel(CSVTYPE::PIT);
    coords_panel = new DataPanel(CSVTYPE::COORDINATE);
    dumps_panel = new DataPanel(CSVTYPE::DUMP);
    roads_panel = new DataPanel(CSVTYPE::ROAD);

    dp_layout->addWidget(pits_panel);
    dp_layout->addWidget(coords_panel);
    dp_layout->addWidget(dumps_panel);
    dp_layout->addWidget(roads_panel);
    dp_layout->setSpacing(0);
    dp_layout->setContentsMargins(0,0,0,0);

    pits_panel->setTitle("PITS");
    coords_panel->setTitle("COORDINATES");
    dumps_panel->setTitle("DUMPS");
    roads_panel->setTitle("ROADS");

    cp_layout = new QVBoxLayout;
    cp_layout->addWidget(GraphicalWindow::instance());
    cp_layout->setContentsMargins(0,0,0,0);
    center_pane->setLayout(cp_layout);

    rp_layout = new QVBoxLayout;
    ver_splitter = new QSplitter(Qt::Vertical, right_pane);
    summary_wgt = new SummaryWindow;
    prev_wgt = new PreviewWindow;
    ver_splitter->addWidget(prev_wgt);
    ver_splitter->addWidget(summary_wgt);
    ver_splitter->setSizes(QList<int>{100,100});
    rp_layout->addWidget(ver_splitter);
    right_pane->setLayout(rp_layout);
    rp_layout->setContentsMargins(0,0,0,0);

    connect(pits_panel, &DataPanel::curDataChanged, prev_wgt, &PreviewWindow::onCurDataChanged);
    connect(roads_panel, &DataPanel::curDataChanged, prev_wgt, &PreviewWindow::onCurDataChanged);
    connect(dumps_panel, &DataPanel::curDataChanged, prev_wgt, &PreviewWindow::onCurDataChanged);
    connect(coords_panel, &DataPanel::curDataChanged, prev_wgt, &PreviewWindow::onCurDataChanged);
    connect(pits_panel, &DataPanel::curDataChanged, summary_wgt, &SummaryWindow::onCurDataChanged);
    connect(dumps_panel, &DataPanel::curDataChanged, summary_wgt, &SummaryWindow::onCurDataChanged);
    connect(coords_panel, &DataPanel::curDataChanged, summary_wgt, &SummaryWindow::onCurDataChanged);
    connect(summary_wgt, &SummaryWindow::pitDumpCntChanged, GraphicalWindow::instance(), &GraphicalWindow::onPitDumpCntChanged);
}

DataEntryWidget *DataEntryWidget::instance()
{
    static DataEntryWidget *singleton = new DataEntryWidget;
    return singleton;
}

QStringList DataEntryWidget::getPitCSVFileNames()
{
    return pits_panel->getCSVFileNames();
}

QStringList DataEntryWidget::getCoordinateCSVFileNames()
{
    return coords_panel->getCSVFileNames();
}

QStringList DataEntryWidget::getDumpCSVFileNames()
{
    return dumps_panel->getCSVFileNames();
}

QStringList DataEntryWidget::getRoadCSVFileNames()
{
    return roads_panel->getCSVFileNames();
}

void DataEntryWidget::setPitCSVFileNames(QStringList pit_csv_files)
{
    pits_panel->setCSVFileNames(pit_csv_files);
}

void DataEntryWidget::setCoordCSVFileNames(QStringList coord_csv_files)
{
    coords_panel->setCSVFileNames(coord_csv_files);
}

void DataEntryWidget::setDumpCSVFileNames(QStringList dump_csv_files)
{
    dumps_panel->setCSVFileNames(dump_csv_files);
}

void DataEntryWidget::setRoadCSVFileNames(QStringList road_csv_files)
{
    roads_panel->setCSVFileNames(road_csv_files);
}

DataEntryWidget::~DataEntryWidget()
{
    delete ui;
}

#include "previewwindow.h"
#include "ui_previewwindow.h"
#include <QDebug>

PreviewWindow::PreviewWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreviewWindow)
{
    ui->setupUi(this);
    action_group = new QActionGroup(this);
    btn_pit = new QAction("PITS");
    btn_dumps = new QAction("DUMPS");
    btn_coordinates = new QAction("COORDINATES");
    btn_roads = new QAction("ROADS");
    action_group->addAction(btn_pit);
    action_group->addAction(btn_dumps);
    action_group->addAction(btn_roads);
    action_group->addAction(btn_coordinates);
    btn_pit->setCheckable(true);
    btn_pit->setChecked(true);
    btn_dumps->setCheckable(true);
    btn_roads->setCheckable(true);
    btn_coordinates->setCheckable(true);
    ui->btn_pit->setDefaultAction(btn_pit);
    ui->btn_dumps->setDefaultAction(btn_dumps);
    ui->btn_roads->setDefaultAction(btn_roads);
    ui->btn_coordinates->setDefaultAction(btn_coordinates);

    pit_table_wgt = new PitTableWidget;
    road_table_wgt = new RoadTableWidget;
    dump_table_wgt = new DumpTableWidget;
    coord_table_wgt = new CoordTableWidget;

    pit_table_wgt->verticalHeader()->hide();
    road_table_wgt->verticalHeader()->hide();
    dump_table_wgt->verticalHeader()->hide();
    coord_table_wgt->verticalHeader()->hide();

    pit_table_wgt->verticalHeader()->setDefaultSectionSize(20);
    road_table_wgt->verticalHeader()->setDefaultSectionSize(20);
    dump_table_wgt->verticalHeader()->setDefaultSectionSize(20);
    coord_table_wgt->verticalHeader()->setDefaultSectionSize(20);

    pit_table_wgt->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    road_table_wgt->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    dump_table_wgt->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    coord_table_wgt->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    pit_table_wgt->horizontalHeader()->setFixedHeight(25);
    road_table_wgt->horizontalHeader()->setFixedHeight(25);
    dump_table_wgt->horizontalHeader()->setFixedHeight(25);
    coord_table_wgt->horizontalHeader()->setFixedHeight(25);

    ui->stkw_tables->addWidget(pit_table_wgt);
    ui->stkw_tables->addWidget(coord_table_wgt);
    ui->stkw_tables->addWidget(dump_table_wgt);
    ui->stkw_tables->addWidget(road_table_wgt);

    connect(action_group, &QActionGroup::triggered, this, &PreviewWindow::tableChanged);

}

PreviewWindow::~PreviewWindow()
{
    delete ui;
}

void PreviewWindow::onCurDataChanged(CSVTYPE type, QString fileName)
{
    QStandardItemModel *model = new QStandardItemModel;
    QStringList header;
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        int lineindex = 0;
        QTextStream in(&file);
        QString hd = file.readLine();
        header = hd.split(",");
        for (int i=0; i<header.count(); i++) {
            header[i] = header[i].trimmed();
        }
        model->setHorizontalHeaderLabels(header);
        while (!in.atEnd()) {
            QString fileLine = in.readLine();
            QStringList lineToken = fileLine.split(",");
            for (int j = 0; j < lineToken.size(); j++) {
                QString value = lineToken.at(j);
                QStandardItem *item = new QStandardItem(value);
                model->setItem(lineindex, j, item);
            }
            lineindex++;
        }
        file.close();
    }

    switch (type) {
    case CSVTYPE::PIT:
        pit_table_wgt->setModel(model);
        btn_pit->setChecked(true);
        tableChanged(btn_pit);
        cur_table = pit_table_wgt;
        break;
    case CSVTYPE::ROAD:
        road_table_wgt->setModel(model);
        btn_roads->setChecked(true);
        tableChanged(btn_roads);
        cur_table = road_table_wgt;
        break;
    case CSVTYPE::COORDINATE:
        coord_table_wgt->setModel(model);
        tableChanged(btn_coordinates);
        btn_coordinates->setChecked(true);
        cur_table = coord_table_wgt;
        break;
    case CSVTYPE::DUMP:
        dump_table_wgt->setModel(model);
        btn_dumps->setChecked(true);
        tableChanged(btn_dumps);
        cur_table = dump_table_wgt;
        break;
    }
    pit_table_wgt->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int c = 0; c < pit_table_wgt->horizontalHeader()->count(); ++c)
    {
        pit_table_wgt->horizontalHeader()->setSectionResizeMode(
                    c, QHeaderView::Stretch);
    }
    coord_table_wgt->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int c = 0; c < coord_table_wgt->horizontalHeader()->count(); ++c)
    {
        coord_table_wgt->horizontalHeader()->setSectionResizeMode(
                    c, QHeaderView::Stretch);
    }
    dump_table_wgt->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int c = 0; c < dump_table_wgt->horizontalHeader()->count(); ++c)
    {
        dump_table_wgt->horizontalHeader()->setSectionResizeMode(
                    c, QHeaderView::Stretch);
    }
    road_table_wgt->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int c = 0; c < dump_table_wgt->horizontalHeader()->count(); ++c)
    {
        dump_table_wgt->horizontalHeader()->setSectionResizeMode(
                    c, QHeaderView::Stretch);
    }
}

void PreviewWindow::tableChanged(QAction *a)
{
    if (a == btn_pit) {
        ui->stkw_tables->setCurrentIndex(0);
    }
    if (a == btn_coordinates) {
        ui->stkw_tables->setCurrentIndex(1);
    }
    if (a == btn_dumps) {
        ui->stkw_tables->setCurrentIndex(2);
    }
    if (a == btn_roads) {
        ui->stkw_tables->setCurrentIndex(3);
    }
}

void PreviewWindow::on_btn_add_clicked()
{
    cur_table->model()->insertRow(cur_table->currentIndex().row()+1);
}

void PreviewWindow::on_btn_remove_clicked()
{
    cur_table->model()->removeRow(cur_table->currentIndex().row());
}

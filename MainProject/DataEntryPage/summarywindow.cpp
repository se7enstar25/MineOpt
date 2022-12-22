#include "summarywindow.h"
#include "ui_summarywindow.h"
#include <QDebug>

SummaryWindow::SummaryWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SummaryWindow)
{
    ui->setupUi(this);
    QStandardItemModel *model = new QStandardItemModel;
    QStringList header;
    header << "Pit/Dump" << "Total Ore Tonnes" << "Total Waste Volume" << "Total Volume";
    model->setHorizontalHeaderLabels(header);
    ui->tbv_summary->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->tbv_summary->setModel(model);
    total_dump.name = "Total Dumps";
    total_pit.name = "Total Pits";
}

SummaryWindow *SummaryWindow::instance()
{
    static SummaryWindow *singleton = new SummaryWindow;
    return singleton;
}

SummaryWindow::~SummaryWindow()
{
    delete ui;
}

void SummaryWindow::onCurDataChanged(CSVTYPE type, QString fileName)
{
    if(type == CSVTYPE::PIT) {
        sum_pit_hash.clear();
        if (fileName == "") {
            pit_loaded = false;
        } else {
            pit_loaded = true;
            pit_list.clear();
            QFile file(fileName);
            file.open(QIODevice::ReadOnly | QIODevice::Text);
            file.readLine();
            while(!file.atEnd()) {
                QString line = file.readLine();
                QStringList data = line.split(",");
                if(data.count() < 11)
                    break;
                Summary pit;
                pit.name = data[0];
                pit.tot = data[6].toDouble();
                pit.twv = data[9].toDouble();
                pit.tv = data[10].toDouble();
                pit_list.append(pit);
            }
            file.close();
        }
    }
    if(type == CSVTYPE::COORDINATE) {
        sum_pit_hash.clear();
        if (fileName == "") {
            coord_loaded = false;
        } else {
            coord_loaded = true;
            pit_hash.clear();
            QFile file(fileName);
            file.open(QIODevice::ReadOnly | QIODevice::Text);
            file.readLine();
            while(!file.atEnd()) {
                QString line = file.readLine();
                QStringList data = line.split(",");
                pit_hash[data[1]] = data[0];
            }
            file.close();
        }
    }
    if(type == CSVTYPE::DUMP) {
        dump_list.clear();
        if (fileName == "") {
            dump_loaded = false;
        } else {
            dump_loaded = true;
            while(dump_list.count())
                dump_list.takeLast();
            dump_hash.clear();
            QFile file(fileName);
            file.open(QIODevice::ReadOnly | QIODevice::Text);
            QStringList dump_names;
            file.readLine();
            while(!file.atEnd()) {
                QString line = file.readLine();
                QStringList data = line.split(",");
                if(data.count() < 10)
                    break;
                if (dump_hash.keys().indexOf(data[0]) == -1) {
                    dump_hash[data[0]] = data[9].toDouble();
                } else {
                    dump_hash[data[0]] += data[9].toDouble();
                }
            }
            QMapIterator<QString, double> i(dump_hash);
            double tv = 0;
            while (i.hasNext()) {
                i.next();
                Summary temp;
                temp.name = i.key();
                temp.tv = i.value();
                dump_list.append(temp);
                tv += i.value();
            }
            total_dump.tv = tv;
            file.close();
        }
    }
    QStandardItemModel *model = new QStandardItemModel;
    QStringList header;
    header << "Pit/Dump" << "Total Ore Tonnes" << "Total Waste Volume" << "Total Volume";
    model->setHorizontalHeaderLabels(header);
    int row = 0;
    if(pit_loaded && coord_loaded) {
        if (pit_hash.count() != pit_list.count()) {
            model->clear();
        } else {
            for (int i=0; i<pit_list.count(); i++) {
                sum_pit_hash[pit_hash[pit_list[i].name]].tv += pit_list[i].tv;
                sum_pit_hash[pit_hash[pit_list[i].name]].tot += pit_list[i].tot;
                sum_pit_hash[pit_hash[pit_list[i].name]].twv += pit_list[i].twv;
            }
        }
        total_pit.tot = total_pit.twv = total_pit.tv = 0;
        QMapIterator<QString, Summary> i(sum_pit_hash);
        while (i.hasNext()) {
            i.next();
            QStandardItem *item_name = new QStandardItem(i.key());
            QStandardItem *item_tot = new QStandardItem(this->locale().toString(i.value().tot, 'g', 20));
            QStandardItem *item_twv = new QStandardItem(this->locale().toString(i.value().twv, 'g', 20));
            QStandardItem *item_tv = new QStandardItem(this->locale().toString(i.value().tv, 'g', 20));
            item_name->setTextAlignment(Qt::AlignCenter);
            item_tot->setTextAlignment(Qt::AlignCenter);
            item_twv->setTextAlignment(Qt::AlignCenter);
            item_tv->setTextAlignment(Qt::AlignCenter);
            model->setItem(row, 0, item_name);
            model->setItem(row, 1, item_tot);
            model->setItem(row, 2, item_twv);
            model->setItem(row, 3, item_tv);
            total_pit.tot += i.value().tot;
            total_pit.twv += i.value().twv;
            total_pit.tv += i.value().tv;
            row ++;
        }
        {
            QStandardItem *item_name = new QStandardItem(total_pit.name);
            QStandardItem *item_tot = new QStandardItem(this->locale().toString(total_pit.tot, 'g', 20));
            QStandardItem *item_twv = new QStandardItem(this->locale().toString(total_pit.twv, 'g', 20));
            QStandardItem *item_tv = new QStandardItem(this->locale().toString(total_pit.tv, 'g', 20));
            item_name->setTextAlignment(Qt::AlignCenter);
            item_tot->setTextAlignment(Qt::AlignCenter);
            item_twv->setTextAlignment(Qt::AlignCenter);
            item_tv->setTextAlignment(Qt::AlignCenter);
            model->setItem(row, 0, item_name);
            model->setItem(row, 1, item_tot);
            model->setItem(row, 2, item_twv);
            model->setItem(row, 3, item_tv);
            row ++;
        }
    }
    if (dump_loaded) {
        for (int x=0; x<dump_list.count(); x++) {
            QString name = dump_list[x].name;
            double tv = dump_list[x].tv;
            QStandardItem *item_name = new QStandardItem(name);
            QStandardItem *item_tv = new QStandardItem(this->locale().toString(tv, 'g', 20));
            item_name->setTextAlignment(Qt::AlignCenter);
            item_tv->setTextAlignment(Qt::AlignCenter);
            model->setItem(row, 0, item_name);
            model->setItem(row, 3, item_tv);
            row ++;
        }
        {
            QString name = total_dump.name;
            double tv = total_dump.tv;
            QStandardItem *item_name = new QStandardItem(name);
            QStandardItem *item_tv = new QStandardItem(this->locale().toString(tv, 'g', 20));
            item_name->setTextAlignment(Qt::AlignCenter);
            item_tv->setTextAlignment(Qt::AlignCenter);
            model->setItem(row, 0, item_name);
            model->setItem(row, 3, item_tv);
        }
    }
    emit pitDumpCntChanged(sum_pit_hash.count(), dump_list.count());
    ui->tbv_summary->setModel(model);
    ui->tbv_summary->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int c = 0; c < ui->tbv_summary->horizontalHeader()->count(); ++c)
    {
        ui->tbv_summary->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
}

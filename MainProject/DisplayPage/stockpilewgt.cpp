#include "stockpilewgt.h"
#include "ui_stockpilewgt.h"
#include <QDebug>

StockPileWgt::StockPileWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StockPileWgt)
{
    ui->setupUi(this);
    stock_cnt = 0;
    year = 1;
    year_model = new QStandardItemModel;
    QStringList header;
    header << "Stock Pile Number" << "Capacity";
    for (int i=1; i<=year; i++)
        header << tr("Year %1").arg(i);
    year_model->setHorizontalHeaderLabels(header);
    ui->tv_stock_year->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->tv_stock_year->setModel(year_model);
    ui->tv_stock_year->verticalHeader()->hide();

    coord_model = new QStandardItemModel;
    header.clear();
    header << "Stock Pile Number" << "X" << "Y" << "Z";
    coord_model->setHorizontalHeaderLabels(header);
    ui->tv_stock_coord->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->tv_stock_coord->setModel(coord_model);
    ui->tv_stock_coord->verticalHeader()->hide();

    connect(year_model, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(onDataChanged(const QModelIndex&, const QModelIndex&)));
}

StockPileWgt::~StockPileWgt()
{
    delete ui;
}

StockPileWgt *StockPileWgt::instance()
{
    static StockPileWgt *singleton = new StockPileWgt;
    return singleton;
}

void StockPileWgt::setYear(int year)
{
    for (int y=this->year; y>year; y--)
        year_model->removeColumn(1+y);
    this->year = year;
    QStringList header;
    header << "Stock Pile Number" << "Capacity";
    for (int i=1; i<=year; i++)
        header << tr("Year %1").arg(i);
    year_model->setHorizontalHeaderLabels(header);
}

void StockPileWgt::onStockAdded()
{
    year_model->insertRow(stock_cnt);
    stock_cnt ++;
    QStandardItem *item = new QStandardItem(tr("Stock %1").arg(stock_cnt));
    item->setEditable(false);
    year_model->setItem(stock_cnt - 1, 0, item);
    QStandardItem *capacity = new QStandardItem("Repeat");
    capacity->setCheckable(true);
    capacity->setEnabled(false);
    year_model->setItem(stock_cnt - 1, 1, capacity);

    coord_model->insertRow(stock_cnt -1);
    QStandardItem *item1 = new QStandardItem(tr("Stock %1").arg(stock_cnt));
    item->setEditable(false);
    coord_model->setItem(stock_cnt - 1, 0, item1);
}

void StockPileWgt::onStockRemoved()
{
    stock_cnt --;
    year_model->removeRow(stock_cnt);
    coord_model->removeRow(stock_cnt);
}

void StockPileWgt::onDataChanged(const QModelIndex &tl, const QModelIndex &/*br*/)
{
    if (tl.column() == 2) {
        if (year_model->item(tl.row(), tl.column())->text() != "")
            year_model->item(tl.row(), 1)->setEnabled(true);
        else
            year_model->item(tl.row(), 1)->setEnabled(false);
    }
    if (tl.column() == 1) {
        if (year_model->item(tl.row(), tl.column())->isEnabled() && year_model->item(tl.row(), tl.column())->checkState() == Qt::Checked) {
            for (int col = 3; col < 2 + year; col ++) {
                QStandardItem *item = new QStandardItem(year_model->item(tl.row(), 2)->text());
                year_model->setItem(tl.row(), col, item);
            }
        }
    }
}

void StockPileWgt::saveYearModel(QString path)
{
    QString textData;
    int rows = year_model->rowCount();
    int columns = year_model->columnCount();

    textData += "Stock Pile Number";
    for (int i=1; i<=year; i++)
        textData += tr(",Year %1").arg(i);
    textData += "\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (j == 1)
                continue;
            textData += year_model->data(year_model->index(i,j)).toString();
            if(j != columns-1)
                textData += ",";      // for .csv file format
        }
        if(i != rows-1)
            textData += "\n";             // (optional: for new line segmentation)
    }

    // [Save to file] (header file <QFile> needed)
    // .csv
    QFile csvFile(path);
    if(csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {

        QTextStream out(&csvFile);
        out << textData;

        csvFile.close();
    }
}

void StockPileWgt::saveCoordModel(QString path)
{
    QString textData;
    int rows = coord_model->rowCount();
    int columns = coord_model->columnCount();

    textData += "Stock Pile Number,X,Y,Z";
    textData += "\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            textData += coord_model->data(coord_model->index(i,j)).toString();
            if(j != columns-1)
                textData += ",";      // for .csv file format
        }
        if(i != rows-1)
            textData += "\n";             // (optional: for new line segmentation)
    }

    // [Save to file] (header file <QFile> needed)
    // .csv
    QFile csvFile(path);
    if(csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {

        QTextStream out(&csvFile);
        out << textData;

        csvFile.close();
    }
}

void StockPileWgt::loadYearModel(QString path)
{
    QFile file(path);
    if (file.open(QIODevice::ReadOnly)) {
        int lineindex = 0;                     // file line counter
        QTextStream in(&file);                 // read to text stream
        in.readLine();
        while (!in.atEnd()) {

            // read one line from textstream(separated by "\n")
            QString fileLine = in.readLine();
            // parse the read line into separate pieces(tokens) with "," as the delimiter
            QStringList lineToken = fileLine.split(",");
            // load parsed data to model accordingly
            for (int j = 1; j < lineToken.size(); j++) {
                QString value = lineToken.at(j);
                QStandardItem *item = new QStandardItem(value);
                year_model->setItem(lineindex, j+1, item);
            }
            lineindex++;
        }
        file.close();
    }
}

void StockPileWgt::loadCoordModel(QString path)
{
    QFile file(path);
    if (file.open(QIODevice::ReadOnly)) {
        int lineindex = 0;                     // file line counter
        QTextStream in(&file);                 // read to text stream
        in.readLine();
        while (!in.atEnd()) {

            // read one line from textstream(separated by "\n")
            QString fileLine = in.readLine();
            // parse the read line into separate pieces(tokens) with "," as the delimiter
            QStringList lineToken = fileLine.split(",");
            // load parsed data to model accordingly
            for (int j = 1; j < lineToken.size(); j++) {
                QString value = lineToken.at(j);
                QStandardItem *item = new QStandardItem(value);
                coord_model->setItem(lineindex, j, item);
            }
            lineindex++;
        }
        file.close();
    }
}

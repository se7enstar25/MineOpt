#include "millwgt.h"
#include "ui_millwgt.h"

MillWgt::MillWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MillWgt)
{
    ui->setupUi(this);
    mill_cnt = 0;
    year = 1;
    max_year_model = new QStandardItemModel;
    QStringList max_header;
    max_header << "Mill Number" << "Max Capacity";
    for (int i=1; i<=year; i++)
        max_header << tr("Year %1").arg(i);
    max_year_model->setHorizontalHeaderLabels(max_header);

    min_year_model = new QStandardItemModel;
    QStringList min_header;
    min_header << "Mill Number" << "Min Capacity";
    for (int i=1; i<=year; i++)
        min_header << tr("Year %1").arg(i);
    min_year_model->setHorizontalHeaderLabels(min_header);

    coord_model = new QStandardItemModel;
    QStringList coord_header;
    coord_header << "Mill Number" << "X" << "Y" << "Z";
    coord_model->setHorizontalHeaderLabels(coord_header);

    ui->tv_max_year->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->tv_max_year->setModel(max_year_model);
    ui->tv_max_year->verticalHeader()->hide();

    ui->tv_min_year->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->tv_min_year->setModel(min_year_model);
    ui->tv_min_year->verticalHeader()->hide();

    ui->tv_coord->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->tv_coord->setModel(coord_model);
    ui->tv_coord->verticalHeader()->hide();

    connect(max_year_model, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(onMaxDataChanged(const QModelIndex&, const QModelIndex&)));
    connect(min_year_model, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(onMinDataChanged(const QModelIndex&, const QModelIndex&)));
}

MillWgt::~MillWgt()
{
    delete ui;
}

MillWgt *MillWgt::instance()
{
    static MillWgt *singleton = new MillWgt;
    return singleton;
}

void MillWgt::setYear(int year)
{
    for (int y=this->year; y>year; y--) {
        max_year_model->removeColumn(1+y);
        min_year_model->removeColumn(1+y);
    }
    this->year = year;
    QStringList max_header;
    max_header << "Mill Number" << "Max Capacity";
    for (int i=1; i<=year; i++)
        max_header << tr("Year %1").arg(i);
    max_year_model->setHorizontalHeaderLabels(max_header);

    QStringList min_header;
    min_header << "Mill Number" << "Min Capacity";
    for (int i=1; i<=year; i++)
        min_header << tr("Year %1").arg(i);
    min_year_model->setHorizontalHeaderLabels(min_header);
}

void MillWgt::onMillAdded()
{
    mill_cnt ++;
    {
        max_year_model->insertRow(mill_cnt-1);
        QStandardItem *item = new QStandardItem(tr("Mill %1").arg(mill_cnt));
        item->setEditable(false);
        max_year_model->setItem(mill_cnt - 1, 0, item);
        QStandardItem *capacity = new QStandardItem("Repeat");
        capacity->setCheckable(true);
        capacity->setEnabled(false);
        max_year_model->setItem(mill_cnt - 1, 1, capacity);
    }
    {
        min_year_model->insertRow(mill_cnt-1);
        QStandardItem *item = new QStandardItem(tr("Mill %1").arg(mill_cnt));
        item->setEditable(false);
        min_year_model->setItem(mill_cnt - 1, 0, item);
        QStandardItem *capacity = new QStandardItem("Repeat");
        capacity->setCheckable(true);
        capacity->setEnabled(false);
        min_year_model->setItem(mill_cnt - 1, 1, capacity);
    }
    {
        coord_model->insertRow(mill_cnt-1);
        QStandardItem *item = new QStandardItem(tr("Mill %1").arg(mill_cnt));
        item->setEditable(false);
        coord_model->setItem(mill_cnt - 1, 0, item);
    }
}

void MillWgt::onMillRemoved()
{
    mill_cnt --;
    min_year_model->removeRow(mill_cnt);
    max_year_model->removeRow(mill_cnt);
    coord_model->removeRow(mill_cnt);
}

void MillWgt::onMinDataChanged(const QModelIndex &tl, const QModelIndex & /*br*/)
{
    if (tl.column() == 2) {
        if (min_year_model->item(tl.row(), tl.column())->text() != "")
            min_year_model->item(tl.row(), 1)->setEnabled(true);
        else
            min_year_model->item(tl.row(), 1)->setEnabled(false);
    }
    if (tl.column() == 1) {
        if (min_year_model->item(tl.row(), tl.column())->isEnabled() && min_year_model->item(tl.row(), tl.column())->checkState() == Qt::Checked) {
            for (int col = 3; col < 2 + year; col ++) {
                QStandardItem *item = new QStandardItem(min_year_model->item(tl.row(), 2)->text());
                min_year_model->setItem(tl.row(), col, item);
            }
        }
    }
}

void MillWgt::saveMinYearModel(QString path)
{
    QString textData;
    int rows = min_year_model->rowCount();
    int columns = min_year_model->columnCount();

    textData += "Mill Number";
    for (int i=1; i<=year; i++)
        textData += tr(",Year %1").arg(i);
    textData += "\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (j == 1)
                continue;
            textData += min_year_model->data(min_year_model->index(i,j)).toString();
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

void MillWgt::saveMaxYearModel(QString path)
{
    QString textData;
    int rows = max_year_model->rowCount();
    int columns = max_year_model->columnCount();

    textData += "Mill Number";
    for (int i=1; i<=year; i++)
        textData += tr(",Year %1").arg(i);
    textData += "\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (j == 1)
                continue;
            textData += max_year_model->data(max_year_model->index(i,j)).toString();
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

void MillWgt::saveCoordModel(QString path)
{
    QString textData;
    int rows = coord_model->rowCount();
    int columns = coord_model->columnCount();

    textData += "Mill Number,X,Y,Z";
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

void MillWgt::loadMinYearModel(QString path)
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
                min_year_model->setItem(lineindex, j+1, item);
            }
            lineindex++;
        }
        file.close();
    }
}

void MillWgt::loadMaxYearModel(QString path)
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
                max_year_model->setItem(lineindex, j+1, item);
            }
            lineindex++;
        }
        file.close();
    }
}

void MillWgt::loadCoordModel(QString path)
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

void MillWgt::onMaxDataChanged(const QModelIndex & tl, const QModelIndex & /*br*/)
{
    if (tl.column() == 2) {
        if (max_year_model->item(tl.row(), tl.column())->text() != "")
            max_year_model->item(tl.row(), 1)->setEnabled(true);
        else
            max_year_model->item(tl.row(), 1)->setEnabled(false);
    }
    if (tl.column() == 1) {
        if (max_year_model->item(tl.row(), tl.column())->isEnabled() && max_year_model->item(tl.row(), tl.column())->checkState() == Qt::Checked) {
            for (int col = 3; col < 2 + year; col ++) {
                QStandardItem *item = new QStandardItem(max_year_model->item(tl.row(), 2)->text());
                max_year_model->setItem(tl.row(), col, item);
            }
        }
    }
}

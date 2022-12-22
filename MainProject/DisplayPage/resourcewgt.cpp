#include "resourcewgt.h"
#include "ui_resourcewgt.h"

ResourceWgt::ResourceWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResourceWgt)
{
    ui->setupUi(this);
    year = 1;
    resource_model = new QStandardItemModel;
    QStringList header;
    header << "Resource" << "Capacity";
    for (int i=1; i<=year; i++)
        header << tr("Year %1").arg(i);
    resource_model->setHorizontalHeaderLabels(header);
    ui->tv_resource->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->tv_resource->setModel(resource_model);
    ui->tv_resource->verticalHeader()->hide();

    resource_model->insertRow(0);
    QStandardItem *item = new QStandardItem("Min");
    item->setEditable(false);
    resource_model->setItem(0, 0, item);
    QStandardItem *capacity = new QStandardItem("Repeat");
    capacity->setCheckable(true);
    capacity->setEnabled(false);
    resource_model->setItem(0, 1, capacity);

    resource_model->insertRow(1);
    QStandardItem *item1 = new QStandardItem("Max");
    item1->setEditable(false);
    resource_model->setItem(1, 0, item1);
    QStandardItem *capacity1 = new QStandardItem("Repeat");
    capacity1->setCheckable(true);
    capacity1->setEnabled(false);
    resource_model->setItem(1, 1, capacity1);

    connect(resource_model, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(onDataChanged(const QModelIndex&, const QModelIndex&)));
}

ResourceWgt::~ResourceWgt()
{
    delete ui;
}

ResourceWgt *ResourceWgt::instance()
{
    static ResourceWgt *singleton = new ResourceWgt;
    return singleton;
}

void ResourceWgt::setYear(int year)
{
    for (int y=this->year; y>year; y--)
        resource_model->removeColumn(1+y);
    this->year = year;
    QStringList header;
    header << "Resource" << "Capacity";
    for (int i=1; i<=year; i++)
        header << tr("Year %1").arg(i);
    resource_model->setHorizontalHeaderLabels(header);
}

void ResourceWgt::onDataChanged(const QModelIndex &tl, const QModelIndex &/*br*/)
{
    if (tl.column() == 2) {
        if (resource_model->item(tl.row(), tl.column())->text() != "")
            resource_model->item(tl.row(), 1)->setEnabled(true);
        else
            resource_model->item(tl.row(), 1)->setEnabled(false);
    }
    if (tl.column() == 1) {
        if (resource_model->item(tl.row(), tl.column())->isEnabled() && resource_model->item(tl.row(), tl.column())->checkState() == Qt::Checked) {
            for (int col = 3; col < 2 + year; col ++) {
                QStandardItem *item = new QStandardItem(resource_model->item(tl.row(), 2)->text());
                resource_model->setItem(tl.row(), col, item);
            }
        }
    }
}

void ResourceWgt::saveResourceModel(QString path)
{
    QString textData;
    int rows = resource_model->rowCount();
    int columns = resource_model->columnCount();

    textData += "Resource";
    for (int i=1; i<=year; i++)
        textData += tr(",Year %1").arg(i);
    textData += "\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (j == 1)
                continue;
            textData += resource_model->data(resource_model->index(i,j)).toString();
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

void ResourceWgt::loadResourceModel(QString path)
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
                resource_model->setItem(lineindex, j+1, item);
            }
            lineindex++;
        }
        file.close();
    }
}

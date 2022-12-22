#include "parameterwidget.h"
#include "ui_parameterwidget.h"
#include <QDebug>

ParameterWidget::ParameterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParameterWidget)
{
    ui->setupUi(this);
    year = 1;
    model = new QStandardItemModel;
    QStringList header;
    header << "Years(t in T)" << "Ore Sell Price(pt) per unit grade" << "Waste Mining Cost(wmt)" << "Wash Cost(ct)" << "Stock Rehandling Cost(rt)";
    model->setHorizontalHeaderLabels(header);
    ui->tv_data->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->tv_data->verticalHeader()->hide();
    model->insertRow(0);
    for (int i=1; i<=year; i++) {
        QStandardItem *item = new QStandardItem(tr("Year %1").arg(i));
        item->setEditable(false);
        model->setItem(i, 0, item);
    }
    for (int i=1; i<=4; i++) {
        QStandardItem *capacity = new QStandardItem("Repeat");
        capacity->setCheckable(true);
        capacity->setEnabled(false);
        model->setItem(0, i, capacity);
    }
    ui->tv_data->setModel(model);
    ui->tv_data->setWordWrap(true);
    ui->tv_data->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int c = 0; c < ui->tv_data->horizontalHeader()->count(); ++c)
    {
        ui->tv_data->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
    connect(model, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(onDataChanged(const QModelIndex&, const QModelIndex&)));
}

ParameterWidget *ParameterWidget::instance()
{
    static ParameterWidget* singleton = new ParameterWidget;
    return singleton;
}

ParameterWidget::~ParameterWidget()
{
    delete ui;
}

void ParameterWidget::onYearChanged(int year)
{
    for (int y=this->year; y>year; y--)
        model->removeRow(y);
    for (int i=1; i<=year; i++) {
        QStandardItem *item = new QStandardItem(tr("Year %1").arg(i));
        item->setEditable(false);
        model->setItem(i, 0, item);
    }
    this->year = year;
}

void ParameterWidget::onDataChanged(const QModelIndex &tl, const QModelIndex &/*br*/)
{
    if (tl.row() == 1 && tl.column() != 0) {
        if (model->item(tl.row(), tl.column())->text() != "")
            model->item(0, tl.column())->setEnabled(true);
        else
            model->item(0, tl.column())->setEnabled(false);
    }
    if (tl.row() == 0) {
        if (model->item(tl.row(), tl.column())->isEnabled() && model->item(tl.row(), tl.column())->checkState() == Qt::Checked) {
            for (int row = 2; row < 1 + year; row ++) {
                QStandardItem *item = new QStandardItem(model->item(1, tl.column())->text());
                model->setItem(row, tl.column(), item);
            }
        }
    }
}

void ParameterWidget::saveModel(QString path)
{
    QString textData;
    int rows = model->rowCount();
    int columns = model->columnCount();

    textData += "Years(t in T),Ore Sell Price(pt) per unit grade,Waste Mining Cost(wmt),Wash Cost(ct),Stock Rehandling Cost(rt)\n";
    for (int i = 1; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            textData += model->data(model->index(i,j)).toString();
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

void ParameterWidget::loadModel(QString path)
{
    QFile file(path);
    if (file.open(QIODevice::ReadOnly)) {
        int lineindex = 1;                     // file line counter
        QTextStream in(&file);                 // read to text stream
        in.readLine();
        while (!in.atEnd()) {

            // read one line from textstream(separated by "\n")
            QString fileLine = in.readLine();
            // parse the read line into separate pieces(tokens) with "," as the delimiter
            QStringList lineToken = fileLine.split(",");
            // load parsed data to model accordingly
            for (int j = 0; j < lineToken.size(); j++) {
                QString value = lineToken.at(j);
                QStandardItem *item = new QStandardItem(value);
                model->setItem(lineindex, j, item);
            }
            lineindex++;
        }
        file.close();
    }
}

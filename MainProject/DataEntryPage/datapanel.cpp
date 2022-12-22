#include "datapanel.h"
#include "ui_datapanel.h"
#include <QDebug>

DataPanel::DataPanel(CSVTYPE type, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataPanel)
{
    ui->setupUi(this);
    this->type = type;
}

void DataPanel::setTitle(QString title)
{
    ui->label->setText(title);
}

DataPanel::~DataPanel()
{
    delete ui;
}

void DataPanel::on_btn_add_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this, "Select one or more files to open",
                            "/home", "CSV Files (*.csv)");
    QStringList file_paths;
    for (int i=0; i<ui->lw_data->count(); i++)
        file_paths.append(ui->lw_data->item(i)->toolTip());
    bool flag = false;
    foreach(QString file, files) {
        if(file_paths.indexOf(file) == -1) {
            QString file_name = file.split("/").last();
            QListWidgetItem *item = new QListWidgetItem(file_name);
            item->setToolTip(file);
            ui->lw_data->addItem(item);
            if (flag == false) {
                flag = true;
                ui->lw_data->setCurrentItem(item);
            }
        }
    }
}

void DataPanel::on_btn_remove_clicked()
{
    ui->lw_data->takeItem(ui->lw_data->currentRow());
    if (ui->lw_data->count())
        on_lw_data_currentRowChanged(ui->lw_data->currentRow());
    else
        on_lw_data_currentRowChanged(-1);
}

void DataPanel::on_lw_data_currentRowChanged(int currentRow)
{
    if (currentRow != -1)
        emit curDataChanged(type, ui->lw_data->item(currentRow)->toolTip());
    else
        emit curDataChanged(type, "");
}

void DataPanel::on_lw_data_itemActivated(QListWidgetItem *item)
{
    emit curDataChanged(type, item->toolTip());
}

QStringList DataPanel::getCSVFileNames()
{
    QStringList csv_file_names;
    for (int i=0; i<ui->lw_data->count(); i++) {
        csv_file_names.append(ui->lw_data->item(i)->toolTip());
    }
    return csv_file_names;
}

void DataPanel::setCSVFileNames(QStringList csv_files)
{
    while(ui->lw_data->count()) {
        ui->lw_data->takeItem(ui->lw_data->count()-1);
    }
    for (int i=0; i<csv_files.count(); i++) {
        QString file_name = csv_files[i].split("/").last();
        QListWidgetItem *item = new QListWidgetItem(file_name);
        item->setToolTip(csv_files[i]);
        ui->lw_data->addItem(item);
        on_lw_data_itemActivated(item);
    }
}

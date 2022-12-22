#ifndef DATAPANEL_H
#define DATAPANEL_H

#include <QWidget>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QStringList>

namespace Ui {
class DataPanel;
}

enum CSVTYPE{PIT, COORDINATE, DUMP, ROAD};

class DataPanel : public QWidget
{
    Q_OBJECT

public:
    explicit DataPanel(CSVTYPE type = CSVTYPE::PIT, QWidget *parent = nullptr);
    void setTitle(QString title);
    inline CSVTYPE getType() { return type; }
    inline void setType(CSVTYPE type) { this->type = type; }
    QStringList getCSVFileNames();
    void setCSVFileNames(QStringList csv_files);
    ~DataPanel();

private slots:
    void on_btn_add_clicked();

    void on_btn_remove_clicked();

    void on_lw_data_currentRowChanged(int currentRow);

    void on_lw_data_itemActivated(QListWidgetItem *item);

signals:
    void curDataChanged(CSVTYPE type, QString fileName);

public:
    QStringList file_names;

private:
    Ui::DataPanel *ui;
    CSVTYPE type;
};

#endif // DATAPANEL_H

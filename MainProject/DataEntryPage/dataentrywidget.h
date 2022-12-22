#ifndef DATAENTRYWIDGET_H
#define DATAENTRYWIDGET_H

#include <QWidget>
#include <QSplitter>
#include <QVBoxLayout>
#include "datapanel.h"
#include "graphicalwindow.h"
#include "previewwindow.h"
#include "summarywindow.h"

namespace Ui {
class DataEntryWidget;
}

class DataEntryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DataEntryWidget(QWidget *parent = nullptr);
    static DataEntryWidget* instance();
    QStringList getPitCSVFileNames();
    QStringList getCoordinateCSVFileNames();
    QStringList getDumpCSVFileNames();
    QStringList getRoadCSVFileNames();

    void setPitCSVFileNames(QStringList pit_csv_files);
    void setCoordCSVFileNames(QStringList coord_csv_files);
    void setDumpCSVFileNames(QStringList dump_csv_files);
    void setRoadCSVFileNames(QStringList road_csv_files);
    ~DataEntryWidget();

public:
    QVBoxLayout *layout, *dp_layout, *cp_layout, *rp_layout;
    QSplitter *splitter, *ver_splitter;
    QFrame *center_pane;

private:
    Ui::DataEntryWidget *ui;
    QFrame *left_pane;
    QFrame *right_pane;
    DataPanel *pits_panel, *coords_panel, *dumps_panel, *roads_panel;
    PreviewWindow *prev_wgt;
    SummaryWindow *summary_wgt;
};

#endif // DATAENTRYWIDGET_H

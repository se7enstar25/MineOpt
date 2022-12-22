#ifndef ROADTABLEWIDGET_H
#define ROADTABLEWIDGET_H

#include <QObject>
#include <QTableWidget>
#include "customitemdelegate.h"

class RoadTableWidget : public QTableView
{
    Q_OBJECT
public:
    RoadTableWidget();

private:
    CustomItemDelegate *item_delegate;
};

#endif // ROADTABLEWIDGET_H

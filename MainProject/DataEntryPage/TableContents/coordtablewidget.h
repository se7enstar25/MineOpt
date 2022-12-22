#ifndef COORDTABLEWIDGET_H
#define COORDTABLEWIDGET_H

#include <QObject>
#include <QTableWidget>
#include "customitemdelegate.h"

class CoordTableWidget : public QTableView
{
    Q_OBJECT
public:
    CoordTableWidget();

private:
    CustomItemDelegate *item_delegate;
};

#endif // COORDTABLEWIDGET_H

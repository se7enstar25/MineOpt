#ifndef DUMPTABLEWIDGET_H
#define DUMPTABLEWIDGET_H

#include <QObject>
#include <QTableWidget>
#include "customitemdelegate.h"

class DumpTableWidget : public QTableView
{
    Q_OBJECT
public:
    DumpTableWidget();

private:
    CustomItemDelegate *item_delegate;
};

#endif // DUMPTABLEWIDGET_H

#ifndef PITTABLEWIDGET_H
#define PITTABLEWIDGET_H

#include <QObject>
#include <QTableWidget>
#include "customitemdelegate.h"

class PitTableWidget : public QTableView
{
    Q_OBJECT
public:
    PitTableWidget();

private:
    CustomItemDelegate *item_delegate;
};

#endif // PITTABLEWIDGET_H

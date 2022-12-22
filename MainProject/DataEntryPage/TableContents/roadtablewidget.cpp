#include "roadtablewidget.h"

RoadTableWidget::RoadTableWidget()
{
    item_delegate = new CustomItemDelegate;
    setItemDelegate(item_delegate);
}

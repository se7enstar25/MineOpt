#include "coordtablewidget.h"

CoordTableWidget::CoordTableWidget()
{
    item_delegate = new CustomItemDelegate;
    setItemDelegate(item_delegate);
}

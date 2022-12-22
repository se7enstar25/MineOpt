#include "pittablewidget.h"

PitTableWidget::PitTableWidget()
{
    item_delegate = new CustomItemDelegate;
    setItemDelegate(item_delegate);
}

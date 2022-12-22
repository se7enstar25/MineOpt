#include "dumptablewidget.h"

DumpTableWidget::DumpTableWidget()
{
    item_delegate = new CustomItemDelegate;
    setItemDelegate(item_delegate);
}

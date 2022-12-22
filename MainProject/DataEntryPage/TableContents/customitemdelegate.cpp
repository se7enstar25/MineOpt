#include "customitemdelegate.h"
#include <QDebug>

CustomItemDelegate::CustomItemDelegate()
{

}

void CustomItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const QString txt = index.data().toString();
    painter->save();
    QStyleOptionViewItem optCopy(option);     // make a copy to modify
    optCopy.displayAlignment = Qt::AlignCenter;
    QStyledItemDelegate::paint(painter, optCopy, index);
    painter->restore();
}

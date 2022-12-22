#ifndef CUSTOMITEMDELEGATE_H
#define CUSTOMITEMDELEGATE_H

#include <QObject>
#include <QItemDelegate>
#include <QEvent>
#include <QPainter>
#include <QStyledItemDelegate>

class CustomItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    CustomItemDelegate();

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // CUSTOMITEMDELEGATE_H

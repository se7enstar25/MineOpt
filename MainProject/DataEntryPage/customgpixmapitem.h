#ifndef CUSTOMGPIXMAPITEM_H
#define CUSTOMGPIXMAPITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

enum GPIType{
    STOCK, MILL, GPIT, GDUMP, ARROW
};

class CustomGPixmapItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    CustomGPixmapItem(GPIType type);
    inline void setName(QString name) { this->name = name; }
    inline QString getName() { return name; }
    ~CustomGPixmapItem();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
    QString name;

public:
    GPIType type;
    bool is_external{true};
    QString lag_distance;
    QString lwpt;

signals:
    void itemRemoved(GPIType type, int id);
    void stockChanged(QString name);

};

#endif // CUSTOMGPIXMAPITEM_H

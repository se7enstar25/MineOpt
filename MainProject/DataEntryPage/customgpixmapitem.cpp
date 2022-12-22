#include "customgpixmapitem.h"
#include <QDebug>

CustomGPixmapItem::CustomGPixmapItem(GPIType type)
{
    switch (type) {
    case GPIType::STOCK:
        setPixmap(QPixmap(":/Assets/png/icon2.0_stockpile.png").scaled(50,50,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        setName("Stock");
        setFlag(QGraphicsItem::ItemIsFocusable);
        break;
    case GPIType::GDUMP:
        setPixmap(QPixmap(":/Assets/png/icon2.0_dump.png").scaled(50,50,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        setName("Dump");
        break;
    case GPIType::GPIT:
        setPixmap(QPixmap(":/Assets/png/icon2.0_pit.png").scaled(50,50,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        setName("Pit");
        break;
    case GPIType::MILL:
        setPixmap(QPixmap(":/Assets/png/icon2.0_mills.png").scaled(50,50,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        setName("MILL");
        setFlag(QGraphicsItem::ItemIsFocusable);
        break;
    case GPIType::ARROW:
        break;
    }
    this->type = type;
    setFlag(QGraphicsItem::ItemIsSelectable);
    this->setTransformationMode(Qt::SmoothTransformation);
}

CustomGPixmapItem::~CustomGPixmapItem()
{

}

void CustomGPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent */*event*/)
{
    if(type == GPIType::GDUMP) {

    }
}

void CustomGPixmapItem::keyPressEvent(QKeyEvent */*event*/)
{
//    if (event->key() == Qt::Key_Delete) {
//        itemRemoved(type, getUniqueId());
//        deleteLater();
//    }
}

void CustomGPixmapItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent */*event*/)
{

}

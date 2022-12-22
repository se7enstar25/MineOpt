#ifndef CUSTOMGRAPHICSSCENE_H
#define CUSTOMGRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsItem>

class CustomGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    CustomGraphicsScene();
    static CustomGraphicsScene* instance();

protected:
    void wheelEvent(QGraphicsSceneWheelEvent *wheelEvent) override;
};

#endif // CUSTOMGRAPHICSSCENE_H

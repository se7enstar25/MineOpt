#include "customgraphicsscene.h"
#include <QDebug>

CustomGraphicsScene::CustomGraphicsScene()
{

}

CustomGraphicsScene *CustomGraphicsScene::instance()
{
    static CustomGraphicsScene *singleton = new CustomGraphicsScene;
    return singleton;
}

void CustomGraphicsScene::wheelEvent(QGraphicsSceneWheelEvent */*wheelEvent*/)
{

}

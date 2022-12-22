#include "graphicalwindow.h"
#include "ui_graphicalwindow.h"
#include <QDebug>

GraphicalWindow::GraphicalWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphicalWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(CustomGraphicsScene::instance());
    ui->graphicsView->fitInView(CustomGraphicsScene::instance()->itemsBoundingRect());
    CustomGraphicsScene::instance()->setSceneRect(0,0,1000,1000);
}

GraphicalWindow *GraphicalWindow::instance()
{
    static GraphicalWindow* singleton = new GraphicalWindow;
    return singleton;
}

void GraphicalWindow::addStock()
{
    stock_cnt ++;
    emit stockAdded();
    reDraw();
}

void GraphicalWindow::addMill()
{
    mill_cnt ++;
    emit millAdded();
    reDraw();
}

void GraphicalWindow::removeStock()
{
    if (stock_cnt == 0)
        return;
    stock_cnt --;
    emit stockRemoved();
    reDraw();
}

void GraphicalWindow::removeMill()
{
    if (mill_cnt == 0)
        return;
    mill_cnt --;
    emit millRemoved();
    reDraw();
}

void GraphicalWindow::onPitDumpCntChanged(int pit_cnt, int dump_cnt)
{
    this->pit_cnt = pit_cnt;
    this->dump_cnt = dump_cnt;
    reDraw();
}

void GraphicalWindow::reDraw()
{
    CustomGraphicsScene::instance()->clear();
    int x = 30, y = 30;
    for(int i = 0; i < pit_cnt; i ++) {
        CustomGPixmapItem *item;
        item = new CustomGPixmapItem(GPIType::GPIT);
        item->setToolTip(item->getName() + " " + tr("%1").arg(i + 1));
        item->setPos(x, y);
        CustomGraphicsScene::instance()->addItem(item);
        QGraphicsTextItem *text_item;
        text_item = new QGraphicsTextItem(tr("Pit %1").arg(i+1));
        text_item->setPos(x, y+50);
        CustomGraphicsScene::instance()->addItem(text_item);
        x += 70;
        if (x == 240)
        {
            x = 0;
            y += 70;
        }
    }
    x = 400;
    y = 30;
    for(int i = 0; i < stock_cnt; i ++) {
        CustomGPixmapItem *item;
        item = new CustomGPixmapItem(GPIType::STOCK);
        item->setToolTip(item->getName() + " " + tr("%1").arg(i + 1));
        item->setPos(x, y);
        CustomGraphicsScene::instance()->addItem(item);
        QGraphicsTextItem *text_item;
        text_item = new QGraphicsTextItem(tr("Stockpile S%1").arg(i+1));
        text_item->setPos(x, y+50);
        CustomGraphicsScene::instance()->addItem(text_item);
        x += 70;
        if (x == 610)
        {
            x = 400;
            y += 70;
        }
    }
    x = 30;
    y = 400;
    for(int i = 0; i < dump_cnt; i ++) {
        CustomGPixmapItem *item;
        item = new CustomGPixmapItem(GPIType::GDUMP);
        item->setToolTip(item->getName() + " " + tr("%1").arg(i + 1));
        item->setPos(x, y);
        CustomGraphicsScene::instance()->addItem(item);
        QGraphicsTextItem *text_item;
        text_item = new QGraphicsTextItem(tr("Dump %1").arg(i+1));
        text_item->setPos(x, y+50);
        CustomGraphicsScene::instance()->addItem(text_item);
        x += 70;
        if (x == 240)
        {
            x = 0;
            y += 70;
        }
    }
    x = 400;
    y = 400;
    for(int i = 0; i < mill_cnt; i ++) {
        CustomGPixmapItem *item;
        item = new CustomGPixmapItem(GPIType::MILL);
        item->setToolTip(item->getName() + " " + tr("%1").arg(i + 1));
        item->setPos(x, y);
        CustomGraphicsScene::instance()->addItem(item);
        QGraphicsTextItem *text_item;
        text_item = new QGraphicsTextItem(tr("Plant M%1").arg(i+1));
        text_item->setPos(x, y+50);
        CustomGraphicsScene::instance()->addItem(text_item);
        x += 70;
        if (x == 610)
        {
            x = 400;
            y += 70;
        }
    }

    for (int i=0; i<pit_cnt; i++) {
        if(stock_cnt) {
            QGraphicsItemGroup *arrow;
            arrow = new QGraphicsItemGroup();
            QGraphicsPixmapItem *arrow_body;
            int arrow_width = 310;
            int arrow_height = 10;
            arrow_body = new QGraphicsPixmapItem(QPixmap(":/Assets/png/icon2.0_arrow_body.png").scaled(arrow_width, arrow_height,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            arrow_body->setTransformationMode(Qt::SmoothTransformation);
            arrow_body->setPos(0, 0);
            arrow->addToGroup(arrow_body);
            QGraphicsPixmapItem *arrow_head;
            arrow_head = new QGraphicsPixmapItem(QPixmap(":/Assets/png/icon2.0_arrow_head.png").scaled(arrow_height, arrow_height,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            arrow_head->setPos(arrow_width,0);
            arrow_head->setTransformationMode(Qt::SmoothTransformation);
            arrow->addToGroup(arrow_head);
            arrow->setPos(80, 50);
            arrow->setFlag(QGraphicsItem::ItemIsSelectable, true);
            CustomGraphicsScene::instance()->addItem(arrow);
        }
        if(dump_cnt) {
            QGraphicsItemGroup *arrow;
            arrow = new QGraphicsItemGroup();
            QGraphicsPixmapItem *arrow_body;
            int arrow_width = 290;
            int arrow_height = 10;
            arrow_body = new QGraphicsPixmapItem(QPixmap(":/Assets/png/icon2.0_arrow_body.png").scaled(arrow_width,arrow_height,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            arrow_body->setTransformationMode(Qt::SmoothTransformation);
            arrow_body->setPos(0, 0);
            arrow->addToGroup(arrow_body);
            QGraphicsPixmapItem *arrow_head;
            arrow_head = new QGraphicsPixmapItem(QPixmap(":/Assets/png/icon2.0_arrow_head.png").scaled(arrow_height,arrow_height,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            arrow_head->setPos(arrow_width,0);
            arrow_head->setTransformationMode(Qt::SmoothTransformation);
            arrow->addToGroup(arrow_head);
            arrow->setPos(65, 100);
            arrow->setRotation(90);
            arrow->setFlag(QGraphicsItem::ItemIsSelectable, true);
            CustomGraphicsScene::instance()->addItem(arrow);
        }
        if (mill_cnt) {
            QGraphicsItemGroup *arrow;
            arrow = new QGraphicsItemGroup();
            QGraphicsPixmapItem *arrow_body;
            int arrow_width = 450;
            int arrow_height = 10;
            arrow_body = new QGraphicsPixmapItem(QPixmap(":/Assets/png/icon2.0_arrow_body.png").scaled(arrow_width, arrow_height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            arrow_body->setTransformationMode(Qt::SmoothTransformation);
            arrow_body->setPos(0, 0);
            arrow->addToGroup(arrow_body);
            QGraphicsPixmapItem *arrow_head;
            arrow_head = new QGraphicsPixmapItem(QPixmap(":/Assets/png/icon2.0_arrow_head.png").scaled(arrow_height, arrow_height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            arrow_head->setPos(arrow_width,0);
            arrow_head->setTransformationMode(Qt::SmoothTransformation);
            arrow->addToGroup(arrow_head);
            arrow->setPos(80, 80);
            arrow->setRotation(45);
            arrow->setFlag(QGraphicsItem::ItemIsSelectable, true);
            CustomGraphicsScene::instance()->addItem(arrow);
        }
    }
}

void GraphicalWindow::onDumpSelectionChanged()
{

}

GraphicalWindow::~GraphicalWindow()
{
    delete ui;
}

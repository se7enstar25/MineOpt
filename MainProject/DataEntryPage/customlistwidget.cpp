#include "customlistwidget.h"
#include <QDebug>
CustomListWidget::CustomListWidget(QWidget *parent) :
    QListWidget(parent)
{
    this->setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
}

void CustomListWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->accept();
    else
        event->ignore();
}

void CustomListWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->ignore();
    }
}

void CustomListWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        QList<QUrl> urls= event->mimeData()->urls();
        QStringList file_paths;
        for (int i=0; i<count(); i++)
            file_paths.append(item(i)->toolTip());
        bool flag = false;
        foreach(QUrl url, urls) {
            if(file_paths.indexOf(url.toLocalFile()) == -1) {
                QString file_name = url.toLocalFile().split("/").last();
                QListWidgetItem *item = new QListWidgetItem(file_name);
                item->setToolTip(url.toLocalFile());
                addItem(item);
                if (flag == false) {
                    flag = true;
                    this->setCurrentItem(item);
                }
            }
        }
        event->setDropAction(Qt::CopyAction);
        event->accept();
    } else {
        event->ignore();
    }
}

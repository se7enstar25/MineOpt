#ifndef GRAPHICALWINDOW_H
#define GRAPHICALWINDOW_H

#include <QWidget>
#include "customgraphicsscene.h"
#include <QGraphicsPixmapItem>
#include "customgpixmapitem.h"
#include "dumpoptionwgt.h"

namespace Ui {
class GraphicalWindow;
}

class GraphicalWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GraphicalWindow(QWidget *parent = nullptr);
    static GraphicalWindow* instance();
    inline int getStockCnt() { return stock_cnt; }
    inline int getMillCnt() { return mill_cnt; }
    inline void setStockCnt(int cnt) {
        for (int i=0; i<stock_cnt; i++)
            emit stockRemoved();
        stock_cnt = cnt;
        for(int i=0; i<cnt; i++)
            emit stockAdded();
    }
    inline void setMillCnt(int cnt) {
        for(int i=0; i<mill_cnt; i++)
            emit millRemoved();
        mill_cnt = cnt;
        for(int i=0; i<cnt; i++) {
            emit millAdded();
        }
    }
    ~GraphicalWindow();

public slots:
    void addStock();
    void addMill();
    void removeStock();
    void removeMill();
    void onPitDumpCntChanged(int pit_cnt, int dump_cnt);
    void reDraw();
    void onDumpSelectionChanged();

signals:
    void stockRemoved();
    void stockAdded();
    void millRemoved();
    void millAdded();
    
private:
    Ui::GraphicalWindow *ui;
    int pit_cnt{0}, dump_cnt{0}, stock_cnt{0}, mill_cnt{0};
};

#endif // GRAPHICALWINDOW_H

#ifndef DUMPOPTIONWGT_H
#define DUMPOPTIONWGT_H

#include <QWidget>

namespace Ui {
class DumpOptionWgt;
}

class DumpOptionWgt : public QWidget
{
    Q_OBJECT

public:
    explicit DumpOptionWgt(QWidget *parent = nullptr);
    static DumpOptionWgt* instance();
    ~DumpOptionWgt();

private:
    Ui::DumpOptionWgt *ui;
};

#endif // DUMPOPTIONWGT_H

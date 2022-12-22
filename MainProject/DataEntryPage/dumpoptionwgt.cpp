#include "dumpoptionwgt.h"
#include "ui_dumpoptionwgt.h"

DumpOptionWgt::DumpOptionWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DumpOptionWgt)
{
    ui->setupUi(this);
}

DumpOptionWgt *DumpOptionWgt::instance()
{
    static DumpOptionWgt *singleton = new DumpOptionWgt;
    return singleton;
}

DumpOptionWgt::~DumpOptionWgt()
{
    delete ui;
}

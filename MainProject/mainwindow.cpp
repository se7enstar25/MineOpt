#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stwgt_cur_page->addWidget(DataEntryWidget::instance());
    ui->stwgt_cur_page->addWidget(DisplayWidget::instance());
    ui->stwgt_cur_page->addWidget(DataAnalysisWidget::instance());
    ui->stwgt_cur_page->addWidget(ParameterWidget::instance());
    ui->stwgt_cur_page->setCurrentIndex(0);
    ui->stwgt_cur_page->setContentsMargins(0,0,0,0);
    action_group = new QActionGroup(this);
    btn_display = new QAction(QIcon(":/Assets/png/icon2.0_display.png"), "Display");
    btn_parameter = new QAction(QIcon(":/Assets/png/icon2.0_parameter.png"), "Parameter");
    btn_data_entry = new QAction(QIcon(":/Assets/png/icon2.0_data entry.png"), "Data entry");
    btn_data_analysis = new QAction(QIcon(":/Assets/png/icon2.0_data anlysis.png"), "Data analysis");
    action_group->addAction(btn_display);
    action_group->addAction(btn_parameter);
    action_group->addAction(btn_data_entry);
    action_group->addAction(btn_data_analysis);

    btn_display->setCheckable(true);
    btn_parameter->setCheckable(true);
    btn_data_entry->setCheckable(true);
    btn_data_entry->setChecked(true);
    btn_data_analysis->setCheckable(true);

    ui->btn_display->setDefaultAction(btn_display);
    ui->btn_parameter->setDefaultAction(btn_parameter);
    ui->btn_data_entry->setDefaultAction(btn_data_entry);
    ui->btn_data_analysis->setDefaultAction(btn_data_analysis);

    connect(action_group, &QActionGroup::triggered, this, &MainWindow::pageChanged);
    connect(DrawingWidget::instance(), &DrawingWidget::yearChanged, ParameterWidget::instance(), &ParameterWidget::onYearChanged);
    DataEntryWidget::instance()->cp_layout->addWidget(GraphicalWindow::instance());
    //setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent */*event*/)
{
    QSize iconSize;
    iconSize.setHeight(ui->frm_page_bar->size().height()/4*3);
    iconSize.setWidth(ui->frm_page_bar->size().height()/4*3);
    ui->btn_data_entry->setIconSize(iconSize);
    ui->btn_data_analysis->setIconSize(iconSize);
    ui->btn_parameter->setIconSize(iconSize);
    ui->btn_display->setIconSize(iconSize);
}

void MainWindow::pageChanged(QAction *a)
{
    if (a == ui->btn_display->defaultAction()) {
        ui->stwgt_cur_page->setCurrentIndex(1);
        DisplayWidget::instance()->cp_layout->addWidget(GraphicalWindow::instance());
    }
    if (a == ui->btn_data_entry->defaultAction()) {
        ui->stwgt_cur_page->setCurrentIndex(0);
        DataEntryWidget::instance()->cp_layout->addWidget(GraphicalWindow::instance());
    }
    if (a == ui->btn_data_analysis->defaultAction()) {
        ui->stwgt_cur_page->setCurrentIndex(2);
    }
    if (a == ui->btn_parameter->defaultAction()) {
        ui->stwgt_cur_page->setCurrentIndex(3);
    }
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_action_Open_triggered()
{
    int ret = QMessageBox::Cancel;
    if(askSave) {
        QMessageBox msgBox;
        msgBox.setText("The project has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        ret = msgBox.exec();
    }
    if(ret == QMessageBox::Save) {
        on_action_Save_triggered();
    }
    QString projectName = QFileDialog::getOpenFileName(this, "Open File",
                                                       "/home", "MineOpt Project (*.mop)");
    if(projectName == "")
        return;
    isNew = false;
    this->projectName = projectName;
    QFile file(this->projectName);

    if(!file.open(QFile::ReadOnly))
    {
        qDebug()<<"Failed to open file in read mode";
    }

    QDomDocument readingDocument;

    if(!readingDocument.setContent(&file))
    {
        qDebug()<<"Failed to set content of file into readinDocument file";
    }

    file.close();

    QDomElement rootNode=readingDocument.firstChildElement();

    QStringList pit_file_names;
    QStringList coord_file_names;
    QStringList dump_file_names;
    QStringList road_file_names;


    QDomElement pitList=rootNode.firstChildElement();
    QDomElement pitItem=pitList.firstChildElement();
    while(!pitItem.isNull())
    {
        if (!QFile::exists(pitItem.attribute("path"))) {
            QMessageBox::warning(this, "File not found!", tr("%1 is not exist.").arg(pitItem.attribute("path")));
            return;
        }
        pit_file_names << pitItem.attribute("path");
        pitItem=pitItem.nextSiblingElement();
    }

    QDomElement coordList=pitList.nextSiblingElement();
    QDomElement coordItem=coordList.firstChildElement();
    while(!coordItem.isNull())
    {
        if (!QFile::exists(coordItem.attribute("path"))) {
            QMessageBox::warning(this, "File not found!", tr("%1 is not exist.").arg(coordItem.attribute("path")));
            return;
        }
        coord_file_names << coordItem.attribute("path");
        coordItem=coordItem.nextSiblingElement();
    }


    QDomElement dumpList=coordList.nextSiblingElement();
    QDomElement dumpItem=dumpList.firstChildElement();
    while(!dumpItem.isNull())
    {
        if (!QFile::exists(dumpItem.attribute("path"))) {
            QMessageBox::warning(this, "File not found!", tr("%1 is not exist.").arg(dumpItem.attribute("path")));
            return;
        }
        dump_file_names << dumpItem.attribute("path");
        dumpItem=dumpItem.nextSiblingElement();
    }


    QDomElement roadList=dumpList.nextSiblingElement();
    QDomElement roadItem=roadList.firstChildElement();
    while(!roadItem.isNull())
    {
        if (!QFile::exists(roadItem.attribute("path"))) {
            QMessageBox::warning(this, "File not found!", tr("%1 is not exist.").arg(roadItem.attribute("path")));
            return;
        }
        road_file_names << roadItem.attribute("path");
        roadItem=roadItem.nextSiblingElement();
    }

    QDomElement yearItem=roadList.nextSiblingElement();
    int cur_year = yearItem.attribute("year").toInt();

    QDomElement stockMillItem = yearItem.nextSiblingElement();

    int stock_cnt = stockMillItem.attribute("stock-cnt").toInt();
    int mill_cnt = stockMillItem.attribute("mill-cnt").toInt();

    DataEntryWidget::instance()->setPitCSVFileNames(pit_file_names);
    DataEntryWidget::instance()->setCoordCSVFileNames(coord_file_names);
    DataEntryWidget::instance()->setDumpCSVFileNames(dump_file_names);
    DataEntryWidget::instance()->setRoadCSVFileNames(road_file_names);

    DisplayWidget::instance()->setYear(cur_year);
    GraphicalWindow::instance()->setStockCnt(stock_cnt);
    GraphicalWindow::instance()->setMillCnt(mill_cnt);
    GraphicalWindow::instance()->reDraw();

    QString parameter_path = this->projectName.left(this->projectName.length()-4) + "_parameters.csv";;
    ParameterWidget::instance()->loadModel(parameter_path);

    QString stock_pile_years_path = this->projectName.left(this->projectName.length()-4) + "_stock_pile_years.csv";
    DisplayWidget::instance()->loadStockPileYearsModel(stock_pile_years_path);
    QString stock_pile_coords_path = this->projectName.left(this->projectName.length()-4) + "_stock_pile_coords.csv";
    DisplayWidget::instance()->loadStockPileCoordsModel(stock_pile_coords_path);
    QString mill_min_years_path = this->projectName.left(this->projectName.length()-4) + "_mill_min_years.csv";
    DisplayWidget::instance()->loadMillMinYearsModel(mill_min_years_path);
    QString mill_max_years_path = this->projectName.left(this->projectName.length()-4) + "_mill_max_years.csv";
    DisplayWidget::instance()->loadMillMaxYearsModel(mill_max_years_path);
    QString mill_coords_path = this->projectName.left(this->projectName.length()-4) + "_mill_coords.csv";
    DisplayWidget::instance()->loadMillCoordsModel(mill_coords_path);
    QString resource_years_path = this->projectName.left(this->projectName.length()-4) + "_resource_years.csv";
    DisplayWidget::instance()->loadResourceModel(resource_years_path);
    askSave = false;
}

void MainWindow::on_action_Save_triggered()
{
    if(isNew) {
        QString projectName = QFileDialog::getSaveFileName(this, "Save File",
                                                           "/home", "MineOpt Project (*.mop)");
        if (projectName == "") {
            return;
        }
        this->projectName = projectName;
    }
    QFile file(this->projectName);

    //opening file in write mode and checking for error
    if(!file.open(QFile::WriteOnly))
    {
        qDebug()<<"example.xml not open in write mode";
    }

    QDomDocument document; //We will create virtual xml document in this QDomDocument.
    QDomElement rootNode=document.createElement("MineOptProject"); //Creating root node of QDomDocument.
    document.appendChild(rootNode); //Appending root node to QDomDocument.

    QStringList pit_files = DataEntryWidget::instance()->getPitCSVFileNames();
    QStringList coord_files = DataEntryWidget::instance()->getCoordinateCSVFileNames();
    QStringList dump_files = DataEntryWidget::instance()->getDumpCSVFileNames();
    QStringList road_files = DataEntryWidget::instance()->getRoadCSVFileNames();
    QDomElement pitList=document.createElement("PitList");
    rootNode.appendChild(pitList);
    for(int i=0; i<pit_files.size(); i++ )
    {
        QDomElement ele= document.createElement("PitItem"); //Element tag created
        ele.setAttribute("path", pit_files[i]);
        pitList.appendChild(ele);   //appending ele as child of root (ele1 was already becomes child of ele)
    }
    QDomElement coordList=document.createElement("CoordList");
    rootNode.appendChild(coordList);
    for(int i=0; i<coord_files.size(); i++ )
    {
        QDomElement ele= document.createElement("CoordItem"); //Element tag created
        ele.setAttribute("path", coord_files[i]);
        coordList.appendChild(ele);   //appending ele as child of root (ele1 was already becomes child of ele)
    }
    QDomElement dumpList=document.createElement("DumpList");
    rootNode.appendChild(dumpList);
    for(int i=0; i<dump_files.size(); i++ )
    {
        QDomElement ele= document.createElement("DumpItem"); //Element tag created
        ele.setAttribute("path", dump_files[i]);
        dumpList.appendChild(ele);   //appending ele as child of root (ele1 was already becomes child of ele)
    }
    QDomElement roadList=document.createElement("RoadList");
    rootNode.appendChild(roadList);
    for(int i=0; i<road_files.size(); i++ )
    {
        QDomElement ele= document.createElement("RoadItem"); //Element tag created
        ele.setAttribute("path", road_files[i]);
        roadList.appendChild(ele);
    }

    QDomElement yearItem=document.createElement("YearItem");
    yearItem.setAttribute("year", DisplayWidget::instance()->getYear());
    rootNode.appendChild(yearItem);

    QString parameter_path = this->projectName.left(this->projectName.length()-4) + "_parameters.csv";
    ParameterWidget::instance()->saveModel(parameter_path);

    QDomElement stockMillItem = document.createElement("StockAndMillItem");
    stockMillItem.setAttribute("stock-cnt", GraphicalWindow::instance()->getStockCnt());
    stockMillItem.setAttribute("mill-cnt", GraphicalWindow::instance()->getMillCnt());
    rootNode.appendChild(stockMillItem);

    QString stock_pile_years_path = this->projectName.left(this->projectName.length()-4) + "_stock_pile_years.csv";
    DisplayWidget::instance()->saveStockPileYearsModel(stock_pile_years_path);

    QString stock_pile_coords_path = this->projectName.left(this->projectName.length()-4) + "_stock_pile_coords.csv";
    DisplayWidget::instance()->saveStockPileCoordsModel(stock_pile_coords_path);

    QString mill_min_years_path = this->projectName.left(this->projectName.length()-4) + "_mill_min_years.csv";
    DisplayWidget::instance()->saveMillMinYearsModel(mill_min_years_path);

    QString mill_max_years_path = this->projectName.left(this->projectName.length()-4) + "_mill_max_years.csv";
    DisplayWidget::instance()->saveMillMaxYearsModel(mill_max_years_path);

    QString mill_coords_path = this->projectName.left(this->projectName.length()-4) + "_mill_coords.csv";
    DisplayWidget::instance()->saveMillCoordsModel(mill_coords_path);

    QString resource_years_path = this->projectName.left(this->projectName.length()-4) + "_resource_years.csv";
    DisplayWidget::instance()->saveResourceModel(resource_years_path);

    QTextStream out(&file);  //It will help to write into file.
    out<<document.toString();    //It will convert QDomDocument to string and will write into file.
    file.close();
    askSave = false;
    isNew = false;
}

void MainWindow::on_actionSave_As_triggered()
{
    isNew = true;
    on_action_Save_triggered();
}

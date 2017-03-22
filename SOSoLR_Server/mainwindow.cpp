#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    startDB_SC();

    startMM();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startDB_SC()
{
    DBmanager *dbmanager = DBmanager::getInstance();
    QThread *thread = new QThread();
    thread->start();
    dbmanager->moveToThread(thread);

    connect(this, SIGNAL(to_read_survival_page(uint)), dbmanager, SLOT(readSurvivalPage(uint)));
    connect(dbmanager, SIGNAL(read_survival_page_finished(QStringList)), this, SLOT(on_read_survival_page_finished(QStringList)));

    connect(this, SIGNAL(to_read_survival_detail(uint)), dbmanager, SLOT(readSurvivalDetail(uint)));
    connect(dbmanager, SIGNAL(read_survival_detail_finished(QStringList)), this, SLOT(on_read_survival_detail_finished(QStringList)));

    connect(this, SIGNAL(to_read_survival_message(uint)), dbmanager, SLOT(readSurvivalMessage(uint)));
    connect(dbmanager, SIGNAL(read_survival_message_finished(QStringList)), this, SLOT(on_read_survival_message_finished(QStringList)));

    connect(dbmanager, SIGNAL(new_survival_arrived(uint)), this, SLOT(on_new_survival_arrived(uint)));
    connect(dbmanager, SIGNAL(new_message_arrived(uint)), this, SLOT(on_new_message_arrived(uint)));

    emit to_read_survival_page(1);

    SerialCom *serialCom = SerialCom::getInstance();
    thread = new QThread();
    thread->start();
    serialCom->moveToThread(thread);

    connect(serialCom, SIGNAL(to_write_survival_detail(QString)), dbmanager, SLOT(writeSurvivalDetail(QString)));
}

void MainWindow::startMM()
{
    MapManager *mapManager = MapManager::getInstance();
    QThread *thread = new QThread();
    thread->start();
    mapManager->moveToThread(thread);

    connect(this, SIGNAL(to_fetch_survival_location(float, float)), mapManager, SLOT(fetchSurvivalLocation(float, float)));
    connect(mapManager, SIGNAL(fetch_survival_location_finished(QPixmap)), this, SLOT(on_fetch_survival_location_finished(QPixmap)));
}

void MainWindow::on_read_survival_page_finished(QStringList stringList)
{
    static QStringListModel *survivalModel = NULL;
    if (!survivalModel)
    {
        survivalModel = new QStringListModel();
        ui->survivalView->setModel(survivalModel);
    }
    survivalModel->setStringList(stringList);
}

void MainWindow::on_read_survival_detail_finished(QStringList stringList)
{
    static QStandardItemModel *conditionModel = NULL;
    if (!conditionModel)
    {
        conditionModel = new QStandardItemModel(6, 2);
        QStringList conditionHeader;
        conditionHeader.append("Item");
        conditionHeader.append("Status");
        conditionModel->setHorizontalHeaderLabels(conditionHeader);
        conditionModel->setItem(0, 0, new QStandardItem("Lon"));
        conditionModel->setItem(1, 0, new QStandardItem("Lat"));
        conditionModel->setItem(2, 0, new QStandardItem("Blood type"));
        conditionModel->setItem(3, 0, new QStandardItem("Mental state"));
        conditionModel->setItem(4, 0, new QStandardItem("Body state"));
        conditionModel->setItem(5, 0, new QStandardItem("Backup food"));
        ui->conditionView->setModel(conditionModel);
        ui->conditionView->verticalHeader()->hide();
    }
    static QStandardItem* item[6] = {NULL};
    for (int i = 0; i < 6; i++)
    {
        delete item[i];
        item[i] = new QStandardItem(stringList[i]);
        conditionModel->setItem(i, 1, item[i]);
    }

    emit to_fetch_survival_location(stringList[0].toFloat(), stringList[1].toFloat());
}

void MainWindow::on_read_survival_message_finished(QStringList stringList)
{
    static QStringListModel *messageModel = NULL;
    if (!messageModel)
    {
        messageModel = new QStringListModel();
        ui->messageView->setModel(messageModel);
    }
    messageModel->setStringList(stringList);
}

void MainWindow::on_fetch_survival_location_finished(QPixmap pix)
{
    ui->mapLabel->setPixmap(pix);
}

void MainWindow::on_sendButton_clicked()
{
    //emit to_send_message(ui->messageEdit->text());
}

void MainWindow::on_lastButton_clicked()
{
    uint currentPage = ui->pageLabel->text().toInt();
    if (currentPage == 1) return;
    ui->pageLabel->setText(QString::number(currentPage - 1));
    emit to_read_survival_page(currentPage - 1);
}

void MainWindow::on_nextButton_clicked()
{
    uint currentPage = ui->pageLabel->text().toInt();
    ui->pageLabel->setText(QString::number(currentPage + 1));
    emit to_read_survival_page(currentPage + 1);
}

void MainWindow::on_survivalView_doubleClicked(const QModelIndex &index)
{   
    ui->mapLabel->setText("LOADING MAP ……");
    emit to_read_survival_detail(index.row() + 1);
    //emit to_read_survival_message(index.row() + 1);
}

void MainWindow::on_new_survival_arrived(uint index)
{
    uint currentPage = ui->pageLabel->text().toInt();
    if ((index < (currentPage - 1) * 10) || (index >= currentPage * 10)) return;
    emit to_read_survival_page(currentPage);
}

void MainWindow::on_new_message_arrived(uint index)
{
    /*
    uint currentSurvival = ui->survivalView->currentIndex().row() + 1;
    if (index != currentSurvival) return;
    emit to_read_survival_message(index);
    */
}

void MainWindow::on_actionSet_Server_port_triggered()
{
    static NewServer *newServer = new NewServer();
    newServer->show();
}

void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

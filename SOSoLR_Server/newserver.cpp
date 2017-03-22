#include "newserver.h"
#include "ui_newserver.h"

NewServer::NewServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewServer)
{
    ui->setupUi(this);
}

NewServer::~NewServer()
{
    delete ui;
}

void NewServer::on_buttonBox_accepted()
{
    static SerialCom *serialcom = SerialCom::getInstance();
    if (!serialcom->bindPort(ui->comboBox->currentIndex())) QMessageBox::critical(this, "Error", "Serial device no found");
}

#include "serialcom.h"
#define WINDOW_SIZE 128

SerialCom::SerialCom()
{
}

SerialCom* SerialCom::SCInstance = NULL;

SerialCom* SerialCom::getInstance()
{
    if (!SCInstance) SCInstance = new SerialCom();
    return SCInstance;
}

void SerialCom::initSC()
{
    serialPort = new QSerialPort();
    serialPort->setBaudRate(9600);
    connect(serialPort, SIGNAL(readyRead()), this, SLOT(on_new_data_ready()));
}

bool SerialCom::bindPort(uint port)
{
    if (!serialPort) initSC();
    serialPort->close();
    serialPort->setPortName("COM" + QString::number(port));
    return serialPort->open(QIODevice::ReadWrite);
}

void SerialCom::sendMessage(QString string)
{

}

void SerialCom::on_new_data_ready()
{
    if (!serialPort->canReadLine()) return;
    //qDebug() << serialPort->readLine(WINDOW_SIZE);
    emit to_write_survival_detail(serialPort->readLine(WINDOW_SIZE));
}

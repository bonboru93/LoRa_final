#ifndef SERIALCOM_H
#define SERIALCOM_H

#include <QSerialPort>
#include <QDebug>
#include <dbmanager.h>

class SerialCom : public QObject
{
    Q_OBJECT

public:
    static SerialCom* getInstance();
    bool bindPort(uint);

signals:
    void to_write_survival_detail(QString);

public slots:
    void sendMessage(QString);

private:
    SerialCom();
    static SerialCom *SCInstance;
    void initSC();
    QSerialPort *serialPort = NULL;

private slots:
    void on_new_data_ready();
};

#endif // SERIALCOM_H

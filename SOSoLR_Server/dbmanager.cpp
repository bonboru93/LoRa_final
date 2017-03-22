#include "dbmanager.h"
#define DATA_PREFIX "[SOSoLR]"
#define DB_NAME "survival.db"

DBmanager::DBmanager()
{
}

DBmanager* DBmanager::DBMInstance = NULL;
DBmanager* DBmanager::getInstance()
{
    if (!DBMInstance) DBMInstance = new DBmanager();
    return DBMInstance;
}

void DBmanager::initDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DB_NAME);
    db.open();
    db.exec("CREATE TABLE `register` ( `id` INTEGER NOT NULL, `name` TEXT, `lat` REAL, `lon` REAL, `p1` INTEGER, `p2` INTEGER, `p3` INTEGER, `p4` INTEGER )");
    db.exec("CREATE TABLE `message` ( `id` INTEGER NOT NULL, `source` INTEGER, `message` TEXT, FOREIGN KEY(`id`) REFERENCES register(id) )");

}

// char-based data format:
// 1. register
// r[id],[name],[lon],[lat],[item1][item2][item3][item4]
// 2. send message
// m[id],[message]
void DBmanager::writeSurvivalDetail(QString data)
{
    if (!db.isOpen()) initDB();
    QStringList dataSet(data.split(","));
    if (dataSet[0] != DATA_PREFIX) return;
    QString cmd;
    uint currentSurvival;
    if (dataSet[1] == "r")
    {
        cmd = "SELECT rowid FROM register WHERE id =" + dataSet[2];
        QSqlQuery result = db.exec(cmd);
        if (result.next())
        {
            //qDebug() << result.value(0).toInt();
            currentSurvival = result.value(0).toInt();
            cmd = "UPDATE register SET lat= " + dataSet[4] + ",lon=" + dataSet[5] + ",p1=" + dataSet[6] + ",p2=" + dataSet[7] + ",p3=" + dataSet[8] + ",p4=" + dataSet[9] + " WHERE rowid=" + QString::number(currentSurvival);
            db.exec(cmd);
            //qDebug() << cmd;
        }
        else
        {
            cmd = "INSERT INTO register VALUES(" + dataSet[2] + ",'" + dataSet[3] + "'," + dataSet[4] + "," + dataSet[5] + "," + dataSet[6] + "," + dataSet[7] + "," + dataSet[8] + "," + dataSet[9] + ")";
            db.exec(cmd);
            cmd = "SELECT rowid FROM register WHERE id =" + dataSet[2];
            QSqlQuery result = db.exec(cmd);
            result.next();
            currentSurvival =  result.value(0).toInt();
        }
    }
    /*
    else if (dataSet[1] == "m")
    {
        cmd = "INSERT INTO message VALUES(" +dataSet[2] + ", 0, '" + dataSet[3] + "')";
        emit new_message_arrived(1);
    }
    */
    qDebug() << currentSurvival;
    emit new_survival_arrived(currentSurvival);
}

void DBmanager::readSurvivalPage(uint page)
{
    if (!db.isOpen()) initDB();
    QSqlQuery result = db.exec("SELECT name FROM register WHERE rowid >" + QString::number((page - 1) * 10) + " AND rowid <=" + QString::number(page * 10));
    QStringList stringList;
    while (result.next())
        stringList.append(result.value(0).toString());
    emit read_survival_page_finished(stringList);
}

void DBmanager::readSurvivalDetail(uint index)
{
    if (!db.isOpen()) initDB();
    QSqlQuery result = db.exec("SELECT lat, lon, p1, p2, p3, p4 FROM register WHERE rowid =" + QString::number(index));
    QStringList stringList;
    result.first();
    stringList.append(result.value(0).toString());
    stringList.append(result.value(1).toString());
    QString temp = result.value(2).toString();
    if (temp == "0") stringList.append("A");
    else if (temp == "1") stringList.append("B");
    else if (temp == "2") stringList.append("AB");
    else stringList.append("O");
    for (int i = 3; i < 5; i++)
    {
        QString temp = result.value(i).toString();
        if (temp == "0") stringList.append("Good");
        else if (temp == "1") stringList.append("Pain");
        else stringList.append("Bad");
    }
    temp = result.value(5).toString();
    if (temp == "0") stringList.append("Full");
    else if (temp == "1") stringList.append("Medium");
    else stringList.append("None");
    emit read_survival_detail_finished(stringList);
}

void DBmanager::readSurvivalMessage(uint index)
{
    /*
    if (!db.isOpen()) initDB();
    QStringList stringList;
    emit read_survival_message_finished(stringList);
    */
}


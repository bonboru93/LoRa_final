#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QPixmap>
#include <QDebug>

class DBmanager : public QObject
{
    Q_OBJECT

public:
    static DBmanager* getInstance();
    void writeData(QString);

signals:
    void read_survival_page_finished(QStringList);
    void read_survival_detail_finished(QStringList);
    void read_survival_message_finished(QStringList);
    void new_survival_arrived(uint);
    void new_message_arrived(uint);

public slots:
    void readSurvivalPage(uint);
    void readSurvivalDetail(uint);
    void readSurvivalMessage(uint);
    void writeSurvivalDetail(QString);

private:
    DBmanager();
    static DBmanager *DBMInstance;
    void initDB();
    QSqlDatabase db;
};

#endif // DBMANAGER_H

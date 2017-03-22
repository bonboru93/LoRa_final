#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QPixmap>

class MapManager : public QObject
{
    Q_OBJECT

public:
    static MapManager* getInstance();

signals:
    void fetch_survival_location_finished(QPixmap);

public slots:
    void fetchSurvivalLocation(float, float);

private:
    MapManager();
    static MapManager *MMInstance;

private slots:
    void on_reply_finished(QNetworkReply*);
};

#endif // MAPMANAGER_H

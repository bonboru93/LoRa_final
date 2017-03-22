#include "mapmanager.h"
#define GOOGLE_MAP_KEY "AIzaSyB_q7IHZRb0nFopOmLdjVXMTf8xoe-iC3w"

MapManager::MapManager()
{
}

MapManager* MapManager::MMInstance = NULL;
MapManager* MapManager::getInstance()
{
    if (!MMInstance) MMInstance = new MapManager();
    return MMInstance;
}

void MapManager::fetchSurvivalLocation(float lon, float lat)
{
    static QNetworkAccessManager *nam = NULL;
    if (!nam)
    {
        nam = new QNetworkAccessManager();
        connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(on_reply_finished(QNetworkReply*)));
    }
    nam->get(QNetworkRequest(QUrl("http://maps.googleapis.com/maps/api/staticmap?size=670x620&scale=1&markers=" + QString::number(lon) + "," + QString::number(lat) + "&key=" + GOOGLE_MAP_KEY)));
}

void MapManager::on_reply_finished(QNetworkReply *reply)
{
    QPixmap pix;
    pix.loadFromData(reply->readAll(), "PNG");
    emit fetch_survival_location_finished(pix);
    delete reply;
}

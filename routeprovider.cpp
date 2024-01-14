#include "routeprovider.h"

RouteProvider::RouteProvider(QObject *parent)
    : QObject{parent}
{
    m_path.clearPath();
}

QGeoPath RouteProvider::geopath()
{
    return m_path;
}

void RouteProvider::setPath(QGeoCoordinate arg)
{
    m_path.addCoordinate(arg);
}

void RouteProvider::pathUpdate(QGeoPath arg)
{
    qDebug() << "update function activated";
    emit pathUpdated(arg);
}

QGeoPath RouteProvider::getPath()
{
    return m_path;
}

void RouteProvider::clearPath()
{
    m_path = QGeoPath();

    m_path.clearPath();
    qDebug() << m_path;
    pathUpdate(m_path);
}

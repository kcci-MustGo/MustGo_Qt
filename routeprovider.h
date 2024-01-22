#ifndef ROUTEPROVIDER_H
#define ROUTEPROVIDER_H

#include <QObject>
#include <QQmlEngine>
#include <qqml.h>
#include <QMetaClassInfo>
#include <QGeoPath>
#include <QVariantList>

class RouteProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QGeoPath geopath READ geopath WRITE pathUpdate NOTIFY pathUpdated)
    QML_ELEMENT

private:
    QGeoPath m_path;

public:
    explicit RouteProvider(QObject *parent = nullptr);
    void setPath(QGeoCoordinate);
    void pathUpdate(QGeoPath);
    Q_INVOKABLE void clearPath();
    QGeoPath getPath();
    QGeoPath geopath();

signals:
    void pathUpdated(QGeoPath);
};

#endif // ROUTEPROVIDER_H

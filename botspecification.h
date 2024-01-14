#ifndef BOTSPECIFICATION_H
#define BOTSPECIFICATION_H

#include <QWidget>
#include <QLabel>
#include <QtLocation>
#include <QtQuickWidgets/QQuickWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QGeoRoute>
#include <QGeoCoordinate>
#include <QVariantList>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qqml.h>
#include <QMetaClassInfo>
#include <QGeoPath>
#include <QDebug>
#include "routeprovider.h"

namespace Ui {
class BotSpecification;
}

class BotSpecification : public QWidget
{
    Q_OBJECT

public:
    explicit BotSpecification(QWidget *parent = nullptr);
    ~BotSpecification();

private:
    Ui::BotSpecification *ui;
    QQuickWidget *pQQuickWidget = new QQuickWidget();
    QWindow *qmlWindow;
    QWidget *qmlWidget;
    QLabel *pQLabel;
    QString tmpUUID;
    QString destName;
    QJsonArray jsonData;
    RouteProvider *pRouteProvider;
    int jsonDataSize;

signals:
    void cancelButtonSig();
    void applyButtonSig(const QString, const QString, const QJsonArray&);
    void getRouteButtonSig(QString);

private slots:
    void getUUIDInBotSpecification(const QString&);
    void setRouteInBotSpecification(QJsonArray);
    void slotButtonGetRouteClicked();
    void slotButtonCancelClicked();
    void slotButtonApplyClicked();

};

#endif // BOTSPECIFICATION_H

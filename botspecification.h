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

namespace Ui {
class BotSpecification;
}

class BotSpecification : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QVariantList path READ getPath NOTIFY setPathChanged)
    Q_PROPERTY(QVariantList currentPos READ getCurrentPos NOTIFY setCurrentPosChanged)

public:
    explicit BotSpecification(QWidget *parent = nullptr);
    ~BotSpecification();
    Q_INVOKABLE void updatePath(const QVariantList &newPath);
    Q_INVOKABLE void updateCurrentPos(const QVariantList &newPos);
    QVariantList getPath() const;
    QVariantList getCurrentPos() const;

private:
    Ui::BotSpecification *ui;
    QQuickWidget *pQQuickWidget = new QQuickWidget();
    QWindow *qmlWindow;
    QWidget *qmlWidget;
    QLabel *pQLabel;
    QString tmpUUID;
    QJsonArray jsonData;
    QVariantList path;
    QVariantList currentPos;
    int jsonDataSize;

signals:
    void cancelButtonSig();
    void getRouteButtonSig(QString);
    void setPathChanged(QVariantList);
    void setCurrentPosChanged();

private slots:
    void getUUIDInBotSpecification(const QString&);
    void getRouteInBotSpecification();
    void setRouteInBotSpecification(QJsonArray);
    void slotButtonCancelClicked();

};

#endif // BOTSPECIFICATION_H

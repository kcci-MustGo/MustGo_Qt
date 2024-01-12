#ifndef FUNCTION_H
#define FUNCTION_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>

class Function : public QObject
{
    Q_OBJECT
public:
    explicit Function(QObject *parent = nullptr);
    void communication();


private:
    QNetworkAccessManager *pQNetworkAccessManger;
    QNetworkReply *pQNetworkReply;
    QByteArray byteArray;
    QJsonArray tmp;
    int emitFlag;

private slots:
    void getContentInBotMainPage();
    void getRouteInBotSpecification(QString);

signals:
    void botMainPageRefresh(QJsonArray);
    void botSpecificationRoute(QJsonArray);

};

#endif // FUNCTION_H

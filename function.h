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

private slots:
    void getContentInBotMainPage();

signals:
    void botMainPageRefresh(QJsonArray);
    void getRouteInBotSpecification(QString);

};

#endif // FUNCTION_H

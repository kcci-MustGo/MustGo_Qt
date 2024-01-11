#include "function.h"

Function::Function(QObject *parent) : QObject(parent)
{
    byteArray = 0;
    pQNetworkAccessManger = new QNetworkAccessManager();

}

void Function::getContentInBotMainPage()
{
    QNetworkRequest request(QUrl("http://52.78.159.10/db/findUser"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    pQNetworkReply = pQNetworkAccessManger->get(request);
    //pQNetworkReply = pQNetworkAccessManger->post(request);

    QObject::connect(pQNetworkReply, &QNetworkReply::finished, this, &Function::communication);
}

void Function::getRouteInBotSpecification(QString)
{
    QNetworkRequest request(QUrl("http://52.78.159.10/map/direction"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

}

void Function::communication()
{
    QJsonDocument jsonDoc;
    if (pQNetworkReply->error() == QNetworkReply::NoError){
        byteArray = pQNetworkReply->readAll();

        QJsonParseError error;
        jsonDoc = QJsonDocument::fromJson(byteArray, &error);
        if (error.error == QJsonParseError::NoError)
        {
            if (jsonDoc.isNull() || jsonDoc.isEmpty())
            {
                qDebug() << "jsonDoc is null or empty";
                tmp = QJsonArray();
            }
            // my jsonDoc is json array not json obj
            else if (jsonDoc.isObject())
            {
                qDebug() << "jsonDoc is not an object";
                qDebug() << jsonDoc;
                tmp = QJsonArray();
            }
            else
            {
                tmp = jsonDoc.array();
            }

            emit botMainPageRefresh(tmp);
        }
    }
    else
        qDebug() << "Err:getContentInBotMainPage()" \
        << pQNetworkReply->errorString();

    pQNetworkReply->deleteLater();
}

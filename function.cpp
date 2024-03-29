#include "function.h"

Function::Function(QObject *parent) : QObject(parent)
{
    byteArray = 0;
    emitFlag = 0;
    pQNetworkAccessManger = new QNetworkAccessManager();

}

void Function::getContentInBotMainPage()
{
    emitFlag = 1;
    QNetworkRequest request(QUrl("http://52.78.159.10/db/findUser"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    pQNetworkReply = pQNetworkAccessManger->get(request);
    //pQNetworkReply = pQNetworkAccessManger->post(request);
    QObject::connect(pQNetworkReply, &QNetworkReply::finished, this, &Function::communication);
}

void Function::getRouteInBotSpecification(QString tmpStr)
{
    emitFlag = 2;
    QNetworkRequest request(QUrl("http://52.78.159.10/map/direction"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QStringList tmpQStringList = tmpStr.split('+');
    QByteArray combinedData = "uuid=" + QUrl::toPercentEncoding(tmpQStringList[0]) + '&' + "destination=" + QUrl::toPercentEncoding(tmpQStringList[1]);
    //qDebug() << combinedData;
    pQNetworkReply = pQNetworkAccessManger->post(request, combinedData);

    QObject::connect(pQNetworkReply, &QNetworkReply::finished, this, &Function::communication);
}


void Function::applyrouteInBotSpecification(const QString arg_uuid, const QString arg_destName, const QJsonArray& arg_json)
{
    //QJsonDocument jsonDoc(arg_json.at(0).toObject().value("route").toArray());
    //qDebug() << arg_json.at(0).toObject().value("route");
    QJsonObject jsonObj = QJsonObject();
    jsonObj.insert("data", arg_json.at(0).toObject().value("route"));
    jsonObj.insert("uuid", arg_uuid);
    jsonObj.insert("name", arg_destName);
    QJsonDocument jsonDoc2(jsonObj);

    QNetworkRequest request(QUrl("http://52.78.159.10/db/addRoute"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QByteArray tmpData = jsonDoc2.toJson(QJsonDocument::Compact);
    qDebug() << "hi";
    pQNetworkReply = pQNetworkAccessManger->post(request, tmpData);

    QObject::connect(pQNetworkReply, &QNetworkReply::finished, this, &Function::communication);

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

            if (emitFlag == 1)
                emit botMainPageRefresh(tmp);
            else if (emitFlag == 2)
                emit botSpecificationRoute(tmp);
            else
            {
                //qDebug() << "Err in Function::communication()";
            }
        }
    }
    else
        qDebug() << "Err:getContentInBotMainPage()" \
        << pQNetworkReply->errorString();

    emitFlag = 0;
    pQNetworkReply->deleteLater();
}

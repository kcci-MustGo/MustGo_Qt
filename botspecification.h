#ifndef BOTSPECIFICATION_H
#define BOTSPECIFICATION_H

#include <QWidget>
#include <QLabel>
#include <QtLocation>
#include <QPixmap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QString>
#include <QDebug>

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
    QLabel *pQLabel;
    QString tmpUUID;
    QJsonArray jsonData;
    int jsonDataSize;

signals:
    void cancelButtonSig();
    void getRouteButtonSig(QString);

private slots:
    void getUUIDInBotSpecification(const QString&);
    void getRouteInBotSpecification();
    void setRouteInBotSpecification(QJsonArray);
    void slotButtonCancelClicked();

};

#endif // BOTSPECIFICATION_H

#include "botspecification.h"
#include "ui_botspecification.h"

BotSpecification::BotSpecification(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BotSpecification)
{
    ui->setupUi(this);
    pQLabel = findChild<QLabel*>("labelMap");
    int mapZoomLevel = 10;
    double mapLatitude =  37.57690;
    double mapLongitude = 126.97765;
    QString tempMapUrl = "https://tile.openstreetmap.org/%1/%2/%3.png";
    QString mapUrl  =
            QString("https://tile.openstreetmap.org/%1/%2/%3.png")\
            .arg(mapZoomLevel).arg(mapLatitude).arg(mapLongitude);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply){
        if (reply->error() == QNetworkReply::NoError){
            QPixmap mapPixmap;
            mapPixmap.loadFromData(reply->readAll());
            if (pQLabel)
                pQLabel->setPixmap(mapPixmap);
        }
        reply->deleteLater();
    });
    manager->get(QNetworkRequest(QUrl(mapUrl)));

    connect(ui->btnSendDestination, SIGNAL(clicked()), this, SLOT(getRoute()));
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(slotButtonCancelClicked()));
}

void BotSpecification::getUUIDInBotSpecification(const QString &UUID)
{
    tmpUUID = UUID;
    qDebug() << tmpUUID;
    // + UPDATE battery reservation
}

void BotSpecification::slotButtonCancelClicked()
{
    emit cancelButtonSig();
}

void BotSpecification::getRoute()
{
    QString tmpAddr = ui->textDestination->toPlainText();
    emit getRouteButtonSig(tmpAddr);
}

BotSpecification::~BotSpecification()
{
    delete ui;
}

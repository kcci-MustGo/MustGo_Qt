#include "botspecification.h"
#include "ui_botspecification.h"

BotSpecification::BotSpecification(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BotSpecification)
{
    ui->setupUi(this);
    jsonDataSize = 0;
    pQLabel = findChild<QLabel*>("labelMap");

    pQQuickWidget = new QQuickWidget();
    //pQQuickWidget = qobject_cast<QQuickWidget*>(ui->layoutMap->widget());
    //pQQuickWidget->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath()+"/MapModule.qml"));
    pQQuickWidget->setSource(QUrl(QStringLiteral("qrc:MapModule.qml")));
    pQQuickWidget->rootContext()->setContextProperty("beautiful", this);

    if (pQQuickWidget->status() == QQuickWidget::Error)
        qDebug() << "pQQuickWidget err" << pQQuickWidget->errors();

    WId winId = pQQuickWidget->winId();
    qmlWindow = QWindow::fromWinId(winId);
    qmlWidget = QWidget::createWindowContainer(qmlWindow, this);

    qmlWidget->resize(500,500);
    ui->layoutMap->addWidget(qmlWidget);

    //pQQuickWidget->show();
    //qmlWindow->show();
    qmlWidget->show();

    connect(ui->btnSendDestination, SIGNAL(clicked()), this, SLOT(getRouteInBotSpecification()));
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(slotButtonCancelClicked()));
}

void BotSpecification::getUUIDInBotSpecification(const QString &UUID)
{
    qmlWidget->show();
    pQQuickWidget->show();
    tmpUUID = UUID;
    qDebug() << tmpUUID;
    // + UPDATE battery reservation
}

void BotSpecification::slotButtonCancelClicked()
{
    qmlWidget->hide();
    emit cancelButtonSig();
}

void BotSpecification::getRouteInBotSpecification()
{
    if (!ui->textDestination->toPlainText().isEmpty())
    {
        QString tmpStr = tmpUUID + '+' + ui->textDestination->toPlainText();
        emit getRouteButtonSig(tmpStr);
    }
}

void BotSpecification::setRouteInBotSpecification(QJsonArray arg)
{
    path.clear();
    currentPos.clear();
    bool startBool = true;

    qDebug() << arg.at(0).toObject();
    QJsonArray tmpArray;

    for ( const QJsonValue &value : arg)
    {
        QJsonObject tmpObj = value.toObject();
        if (tmpObj.contains("route"))
        {
            tmpArray = tmpObj["route"].toArray();
            for (const QJsonValue &coordinate : tmpArray)
            {
                QJsonArray coordinateArray = coordinate.toArray();
                qDebug() << coordinateArray.at(0).toVariant().toString() << coordinateArray.at(1).toVariant().toString().toDouble();
                qDebug() << qSetRealNumberPrecision(10) << coordinateArray.at(0).toDouble() << coordinateArray.at(1).toDouble();
                /*
                if (startBool)
                {
                    currentPos.append(QVariant::fromValue(QGeoCoordinate(coordinateArray.at(0).toDouble(), coordinateArray.at(1).toDouble())));
                    startBool = false;
                }
                else
                    path.append(QVariant::fromValue(QGeoCoordinate(coordinateArray.at(0).toDouble(),coordinateArray.at(1).toDouble())));
                    */
                path.append(QVariant::fromValue(QGeoCoordinate(coordinateArray.at(1).toDouble(),coordinateArray.at(0).toDouble())));
            }

            updatePath(path);
        }
    }
    /*
    QJsonObject qjo = arg.at(0).toObject()["route"].toArray();
    qDebug() << qjo[0];
    qDebug() << qjo["route"][0].toArray()[0].toDouble();
    qDebug() << qjo["route"][0].toArray()[1];

    qDebug() << arg.at(1).toObject();
    */
}

QVariantList BotSpecification::getPath() const
{
    return path;
}

QVariantList BotSpecification::getCurrentPos() const
{
}

void BotSpecification::updatePath(const QVariantList &newPath)
{
    path = newPath;
    emit setPathChanged(path);
}

void BotSpecification::updateCurrentPos(const QVariantList &newPos)
{
}


BotSpecification::~BotSpecification()
{
    delete ui;
}

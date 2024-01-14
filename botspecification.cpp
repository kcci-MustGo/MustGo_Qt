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
    pRouteProvider = new RouteProvider();
    pQQuickWidget->rootContext()->setContextProperty("routeProvider", pRouteProvider);
    pQQuickWidget->setSource(QUrl(QStringLiteral("qrc:MapModule.qml")));

    if (pQQuickWidget->status() == QQuickWidget::Error)
        qDebug() << "pQQuickWidget err" << pQQuickWidget->errors();

    WId winId = pQQuickWidget->winId();
    qmlWindow = QWindow::fromWinId(winId);
    qmlWidget = QWidget::createWindowContainer(qmlWindow, this);

    qmlWidget->resize(500,500);
    ui->layoutMap->addWidget(qmlWidget);

    qmlWidget->show();

    connect(ui->btnSendDestination, SIGNAL(clicked()), this, SLOT(slotButtonGetRouteClicked()));
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(slotButtonCancelClicked()));
    connect(ui->btnApply, SIGNAL(clicked()), this, SLOT(slotButtonApplyClicked()));
}

void BotSpecification::getUUIDInBotSpecification(const QString &UUID)
{
    qmlWidget->show();
    pQQuickWidget->show();
    tmpUUID = UUID;
    ui->labelTitle->setText(tmpUUID);
    destName = QString();
    jsonData = QJsonArray();
    // + UPDATE battery reservation
    // + UPDATE text and map json if already dest exists
}

void BotSpecification::slotButtonCancelClicked()
{
    ui->textDestination->clear();
    pRouteProvider->clearPath();
    pQQuickWidget->repaint();
    qmlWidget->hide();
    emit cancelButtonSig();
}

void BotSpecification::slotButtonGetRouteClicked()
{
    if (!ui->textDestination->toPlainText().isEmpty())
    {
        destName = ui->textDestination->toPlainText();
        QString tmpStr = tmpUUID + '+' + destName;
        emit getRouteButtonSig(tmpStr);
    }
}

void BotSpecification::slotButtonApplyClicked()
{
    ui->btnApply->setChecked(true);
    ui->btnApply->setText("APPLIED");
    emit applyButtonSig(tmpUUID, destName, jsonData);
}

void BotSpecification::setRouteInBotSpecification(QJsonArray arg)
{
    //bool startBool = true;

    //qDebug() << arg.at(0).toObject();
    jsonData = arg;
    //qDebug() << "jsondata" << jsonData;
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
                //qDebug() << coordinateArray.at(0).toVariant().toString() << coordinateArray.at(1).toVariant().toString().toDouble();
                //qDebug() << qSetRealNumberPrecision(10) << coordinateArray.at(0).toDouble() << coordinateArray.at(1).toDouble();
                /*
                if (startBool)
                {
                    currentPos.append(QVariant::fromValue(QGeoCoordinate(coordinateArray.at(0).toDouble(), coordinateArray.at(1).toDouble())));
                    startBool = false;
                }
                else
                    path.append(QVariant::fromValue(QGeoCoordinate(coordinateArray.at(0).toDouble(),coordinateArray.at(1).toDouble())));
                    */
                pRouteProvider->setPath(QGeoCoordinate(coordinateArray.at(1).toDouble(), coordinateArray.at(0).toDouble()));
            }
            pRouteProvider->pathUpdate(pRouteProvider->getPath());
        }
    }
    qDebug() << "setRouteBtnClicked()";
}

BotSpecification::~BotSpecification()
{
    delete ui;
}

#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    pQStackedWidget = new QStackedWidget(this);
    pBotMainPage = new BotMainPage(this);
    pBotSpecification = new BotSpecification(this);
    pQStackedWidget->addWidget(pBotMainPage);
    pQStackedWidget->addWidget(pBotSpecification);

    pQVLayout = findChild<QVBoxLayout*>("layoutDefault");
    pQVLayout->addWidget(pQStackedWidget);
    pBotMainPage->show();
    pBotSpecification->hide();

    Function *pFunction = new Function(this);

    // refresh button in BotMainPage
    connect(pBotMainPage, SIGNAL(refreshButtonSig()), pFunction, SLOT(getContentInBotMainPage()));
    connect(pFunction, SIGNAL(botMainPageRefresh(QJsonArray)), pBotMainPage, SLOT(setContentInBotMainPage(QJsonArray)));

    // getroute button in BotSpecification
    connect(pBotSpecification, SIGNAL(getRouteButtonSig(QString)), pFunction, SLOT(getRouteInBotSpecification(QString)));
    connect(pFunction, SIGNAL(botSpecificationRoute(QJsonArray)), pBotSpecification, SLOT(setRouteInBotSpecification(QJsonArray)));

    // setting button and transit screen to BotSpecification
    connect(pBotMainPage, SIGNAL(settingButtonSig(const QString&)), this, SLOT(screenTransitionToSpecInMainWidget(const QString&)));
    connect(this, SIGNAL(mainWidgetBotSpecificationSig(const QString&)), pBotSpecification, SLOT(getUUIDInBotSpecification(const QString&)));

    // apply button
    connect(pBotSpecification, SIGNAL(applyButtonSig(const QString, const QString, const QJsonArray&)), pFunction, SLOT(applyrouteInBotSpecification(const QString, const QString, const QJsonArray&)));

    // close button and transition to BotMainpage Screen Without modification
    connect(pBotSpecification, SIGNAL(cancelButtonSig()), this, SLOT(screenTransitionToMainInMainWidget()));
}

void MainWidget::screenTransitionToSpecInMainWidget(const QString& UUID)
{
    pBotMainPage->hide();
    pBotSpecification->show();
    emit mainWidgetBotSpecificationSig(UUID);
}

void MainWidget::screenTransitionToMainInMainWidget()
{
    pBotSpecification->hide();
    pBotMainPage->show();
}

MainWidget::~MainWidget()
{
    delete ui;
}


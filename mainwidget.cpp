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


    // transition to BotSpecification Screen
    connect(pBotMainPage, SIGNAL(settingButtonSig(const QString&)), this, SLOT(screenTransitionToSpec(const QString&)));
    connect(this, SIGNAL(settingBotSpecificationSig(const QString&)), pBotSpecification, SLOT(getUUIDInBotSpecification(const QString&)));

    //transition to BotMainpage Screen Without modification
    connect(pBotSpecification, SIGNAL(cancelButtonSig()), this, SLOT(screenTransitionToMain()));
}

void MainWidget::screenTransitionToSpec(const QString& UUID)
{
    pBotMainPage->hide();
    pBotSpecification->show();
    emit settingBotSpecificationSig(UUID);
}

void MainWidget::screenTransitionToMain()
{
    pBotSpecification->hide();
    pBotMainPage->show();
}

MainWidget::~MainWidget()
{
    delete ui;
}


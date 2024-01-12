#include "botmainpage.h"
#include "ui_botmainpage.h"

BotMainPage::BotMainPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BotMainPage)
{
    ui->setupUi(this);
    pQSignalMapper = new QSignalMapper(this);
    connect(ui->buttonRefresh, SIGNAL(clicked()), this, SLOT(slotButtonRefreshClicked()));
}

void BotMainPage::slotButtonRefreshClicked()
{
    emit refreshButtonSig();
}

void BotMainPage::setContentInBotMainPage(QJsonArray tmp)
{
    jsonData = tmp;

    QWidget *scrollWidget = ui->areaScroll->widget();
    QVBoxLayout *scrollLayout = qobject_cast<QVBoxLayout*>(scrollWidget->layout());

    QLayoutItem *itemScrollLayout;
    if (!scrollWidget)
        qDebug() << "scrollwidget is null";
    if (!scrollLayout)
        qDebug() << "scrolllayout is null";
    while ( (itemScrollLayout = scrollLayout->takeAt(0)) != nullptr)
    {
        delete itemScrollLayout->widget();
        delete itemScrollLayout;
    }

    int cnt = 1;
    for (const auto& i : tmp )
    {
        if ( i.isObject() )
        {
            QJsonObject j = i.toObject();

            QLabel *labelID = new QLabel(QString::number(j["ID"].toInt()));
            QLabel *labelUUID = new QLabel(QString(j["UUID"].toString()));
            QLabel *labelNavigation = new QLabel(QString(j["NAVIGATION"].toString()));
            QLabel *labelIP = new QLabel(QString(j["IP"].toString()));
            QPushButton *buttonID = new QPushButton(QString::number(j["ID"].toInt()));

            labelID->setText(QString::number(cnt++));
            labelUUID->setText(QString(j["UUID"].toString()));
            if (j["NAVIGATION"].toString().isNull() || j["NAVIGATION"].toString().isEmpty())
                labelNavigation->setText(QString("NULL"));
            else
                labelNavigation->setText(QString("EXISTS"));
            labelIP->setText(QString(j["IP"].toString()));
            buttonID->setText((QString("setting")));

            QHBoxLayout *row = new QHBoxLayout;
            row->setAlignment(Qt::AlignTop);
            row->addWidget(labelID);
            row->addWidget(labelUUID);
            row->addWidget(labelNavigation);
            row->addWidget(buttonID);

            connect(buttonID, SIGNAL(clicked()), pQSignalMapper, SLOT(map()));
            pQSignalMapper->setMapping(buttonID, QString(j["UUID"].toString()));
            //connect(pQSignalMapper, SIGNAL(mappedString(QString)), this, SLOT(buttonParameterMapper(QString)));
            connect(pQSignalMapper, SIGNAL(mapped(QString)), this, SLOT(buttonParameterMapper(QString)));

            scrollLayout->addLayout(row);
        }
    }
}

void BotMainPage::buttonParameterMapper(QString UUID)
{
    emit settingButtonSig(UUID);
}

BotMainPage::~BotMainPage()
{
    delete ui;
}

#include "botspecification.h"
#include "ui_botspecification.h"

BotSpecification::BotSpecification(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BotSpecification)
{
    ui->setupUi(this);
}

BotSpecification::~BotSpecification()
{
    delete ui;
}

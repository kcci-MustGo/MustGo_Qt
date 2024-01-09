#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    /*
     * 1. txt : NO
     * 2. txt : UUID
     * 3. txt : DESTINATION
     * 4. btn : to specification
     */
}

MainWidget::~MainWidget()
{
    delete ui;
}


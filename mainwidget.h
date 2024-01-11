#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QLayout>
#include <QJsonObject>
#include "botmainpage.h"
#include "botspecification.h"
#include "function.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    Ui::MainWidget *ui;
    QWidget *pBotMainPage;
    QWidget *pBotSpecification;
    QStackedWidget *pQStackedWidget;
    QVBoxLayout *pQVLayout;

signals:
    void settingBotSpecificationSig(const QString&);

private slots:
    void screenTransitionToSpec(const QString&);
    void screenTransitionToMain();
};
#endif // MAINWIDGET_H

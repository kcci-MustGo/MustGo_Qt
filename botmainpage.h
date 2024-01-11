#ifndef BOTMAINPAGE_H
#define BOTMAINPAGE_H

#include <QWidget>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QSignalMapper>
#include <QDebug>

namespace Ui {
class BotMainPage;
}

class BotMainPage : public QWidget
{
    Q_OBJECT

public:
    explicit BotMainPage(QWidget *parent = nullptr);
    ~BotMainPage();

private:
    Ui::BotMainPage *ui;
    QWidget *pQWidget;
    QSignalMapper *pQSignalMapper;
    QJsonArray jsonData;

signals:
    void refreshButtonSig(void);
    void settingButtonSig(const QString&);

private slots:
    void slotButtonRefreshClicked();
    void setContentInBotMainPage(QJsonArray);
    void buttonParameterMapper(const QString&);
};

#endif // BOTMAINPAGE_H

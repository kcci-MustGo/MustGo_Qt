#ifndef BOTSPECIFICATION_H
#define BOTSPECIFICATION_H

#include <QWidget>

namespace Ui {
class BotSpecification;
}

class BotSpecification : public QWidget
{
    Q_OBJECT

public:
    explicit BotSpecification(QWidget *parent = nullptr);
    ~BotSpecification();

private:
    Ui::BotSpecification *ui;
};

#endif // BOTSPECIFICATION_H

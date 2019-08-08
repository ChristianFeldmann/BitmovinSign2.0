#pragma once
#include <QWidget>
class debugger_widget : public QWidget
{
    Q_OBJECT

public:
    debugger_widget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

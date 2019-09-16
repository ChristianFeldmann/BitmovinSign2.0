#pragma once

#include <QWidget>
#include <QPainter>
#include <QPointF>
#include <QTimer>

#include "AnimationStack.h"
#include "Constants.h"
#include "RenderMemory.h"

class DebuggerWidget : public QWidget
{
    Q_OBJECT

public:
    DebuggerWidget(QWidget *parent = nullptr);
    
    void draw(QStringList animationNames, RenderMemory *renderMemory);

    QSize getRenderSegmentSize() const;

protected:
    
    void paintEvent(QPaintEvent *event) override;

    static void drawImage(QPainter &painter, QRect where, const QImage &image);
    static void drawRect(QPainter &painter, QRect where, QString lable = "", bool fillBlack=false);
    
    RenderMemory *renderMemory{ nullptr };
    QStringList animationNames;
};

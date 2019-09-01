#pragma once

#include "AnimationTreeBase.h"
#include "AnimationParameter.h"
#include "Constants.h"
#include "Frame.h"

#include <QImage>

class AnimationBase : public AnimationTreeBase
{
public:
    AnimationBase() = delete;
    AnimationBase(AnimationTreeBase *parentStack);
    virtual ~AnimationBase() = default;

    // Overload from AnimationTreeBase
    virtual AnimationTreeBase *child(int number) override;
    virtual size_t childCount() const override;
    virtual int childNumber(AnimationTreeBase *child) const override;
    virtual QVariant data(int column) const override;

    virtual bool removeChildren(int pos, int rows) override;

    // Reimplement this function and fill the LED data for the frame.
    // The function should return true if the animation ended. Some animations
    // may always return true because they don't have a specific beginning and end.
    // If your animation uses the image to draw a 2D image, don't forget to call 
    // convertImageToFrame to convert the output to a frame.
    virtual bool renderFrame(Frame &frame, QImage &image) = 0;

    virtual QString getName() const = 0;
    void setPropertie(QString propertieName, QString value);

    virtual void reset() {};

protected:
    void convertImageToFrame(Frame &frame, QImage &image);

    std::vector<std::shared_ptr<AnimationParameter>> animationParameters;

    virtual void createPropertiesWidget() override;

private:
    std::vector<QPoint> ledsCoord;

    void calculateLedsCoord();

    void draw_lines_from_points(std::vector<QPointF> point_list, std::vector<unsigned> led_list, int factor);
    void draw_dots_line(QPointF start, QPointF end, unsigned num_of_dots);
};

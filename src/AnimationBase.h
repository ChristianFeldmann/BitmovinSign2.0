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
    virtual AnimationTreeBase *child(int number) const override;
    virtual size_t childCount() const override;
    virtual int childNumber(AnimationTreeBase *child) const override;
    virtual QVariant data(int column) const override;

    virtual bool removeChildren(int pos, int rows) override;

    // Reimplement this function and fill the LED data for the frame.
    // If your animation uses the image to draw a 2D image, don't forget to call 
    // convertImageToFrame to convert the output to a frame.
    virtual void renderFrame(Frame &frame, QImage &image) = 0;

    virtual AnimationState getState() = 0;

    virtual QString getName() const = 0;
    bool usesImage() { return this->imageUsed; }

    virtual void reset() {};

    bool savePlaylist(QDomElement &plist) const override;
    bool loadProperties(QDomElement &plist);

protected:
    void convertImageToFrame(Frame &frame, QImage &image);

    std::vector<std::shared_ptr<AnimationParameter>> animationParameters;
    void addParameter(QString name, QColor *color);
    void addParameter(QString name, int *value);
    void addParameter(QString name, unsigned *value);
    void addParameter(QString name, float *value);
    void addParameter(QString name, int *enumInteger, QStringList enumValues);

    virtual void createPropertiesWidget() override;

private:
    std::vector<QPoint> ledsCoord;
    bool imageUsed{ false };

    void calculateLedsCoord();

    void draw_lines_from_points(std::vector<QPointF> point_list, std::vector<unsigned> led_list, int factor);
    void draw_dots_line(QPointF start, QPointF end, unsigned num_of_dots);

    virtual ItemType getItemType() const { return Animation; }
};

#pragma once

#include "AnimationBase.h"

class AnimationHighlightSparkling: public AnimationBase
{
public:
    AnimationHighlightSparkling() = delete;
    AnimationHighlightSparkling(AnimationTreeBase *parentStack);

    virtual void renderFrame(Frame &frame, QImage &image) override;
    virtual AnimationState getState() override { return AnimationState::Infinite; }
    virtual QString getName() const override { return "HighlightSparkling"; }
    void reset() override;

private:
    struct Spark
    {
        unsigned int position{ 0 };
        float counter{ 0 };
    };
    std::vector<Spark> sparks;

    unsigned getRelativeIndexWrap(unsigned int idx, int offset);

    QColor sparkColor{ Qt::white };
    float sparkSpeed{ 1.0 };
    float sparkRate{ 20.0 };

    float sparkCreationCounter{ 0.0 };
};


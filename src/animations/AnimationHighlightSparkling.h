#pragma once

#include "AnimationBase.h"

class AnimationHighlightSparkling: public AnimationBase
{
public:
    AnimationHighlightSparkling() = delete;
    AnimationHighlightSparkling(AnimationTreeBase *parentStack);

    virtual bool renderFrame(Frame &frame, QImage &image) override;
    virtual QString getName() const override { return "HighlightSparkling"; }
    void reset() override;

private:
    struct Spark
    {
        unsigned int position{ 0 };
        unsigned int counter{ 0 };
    };
    std::vector<Spark> sparks;

    unsigned getRelativeIndexWrap(unsigned int idx, int offset);

    QColor sparkColor{ Qt::white };
    unsigned int offsetCounter{ 0 };
};


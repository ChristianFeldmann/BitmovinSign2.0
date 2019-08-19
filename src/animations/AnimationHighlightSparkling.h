#pragma once

#include <AnimationInterface.h>
#include <Constants.h>

class AnimationHighlightSparkling: public AnimationInterface
{
public:
    AnimationHighlightSparkling();

    bool renderFrame() override;
    virtual QString getName() override { return "HighlightSparkling"; }
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


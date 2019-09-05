#include "AnimationHighlightRotation.h"

#include<assert.h>

AnimationHighlightRotation::AnimationHighlightRotation(AnimationTreeBase *parentStack) :
    AnimationBase(parentStack)
{
    QStringList names = QStringList() << "Background" << "Left" << "Middle" << "Right";
    for (size_t i = 0; i < 4; i++)
    {
        this->addParameter("speed" + names[i], &this->runSpeed[i]);
        this->addParameter("color " + names[i], &this->color[i]);
        this->addParameter("stripes " + names[i], &this->nrStripes[i]);
        this->addParameter("length " + names[i], &this->stripeLength[i]);
    }
}

void AnimationHighlightRotation::reset()
{
    this->rotationCounters[0] = 0;
    this->rotationCounters[1] = 0;
    this->rotationCounters[2] = 0;
    this->rotationCounters[3] = 0;
}

bool AnimationHighlightRotation::renderFrame(Frame &frame, QImage &image)
{
    Q_UNUSED(image);
    frame.clearFrame();

    auto eps = std::numeric_limits<float>::epsilon();

    for (size_t j = 0; j < 4; j++)
    {
        const unsigned ledStartOffset = OFFSET_LIST[j];
        const unsigned nrLed = NR_LED_LIST[j];
        const float internalShift = this->rotationCounters[j];
        const unsigned nrStripes = this->nrStripes[j];
        const float stripeLength = this->stripeLength[j];

        const float distance = float(nrLed) / nrStripes;
        for (size_t stripeIndex = 0; stripeIndex < nrStripes; stripeIndex++)
        {
            float startPos = distance * stripeIndex + internalShift;

            int lengthLedRender = int(std::ceil(stripeLength)) + 1;
            for (unsigned i = 0; i < lengthLedRender; i++)
            {
                unsigned ledPos = unsigned(std::floor(startPos)) + i;

                QColor c = this->color[j];
                if (i == 0 || i == lengthLedRender - 1)
                {
                    float factor;
                    if (i == 0)
                    {
                        factor = std::ceil(startPos + eps) - startPos;
                    }
                    else
                    {
                        factor = startPos - std::floor(startPos);
                    }
                    assert(factor >= 0 && factor <= 1);
                    float alpha = float(c.alpha());
                    int newAlpha = clip(int(alpha * factor), 0, 255);
                    c.setAlpha(newAlpha);
                }
                
                if (ledPos >= nrLed)
                {
                    ledPos -= nrLed;
                }
                frame.data[ledStartOffset + ledPos] = c;
            }
        }

        this->rotationCounters[j] += this->runSpeed[j];
        if (this->runSpeed[j] < 0 && this->rotationCounters[j] < 0)
        {
            this->rotationCounters[j] += nrLed;
        }
        if (this->runSpeed[j] > 0 && this->rotationCounters[j] > nrLed)
        {
            this->rotationCounters[j] -= nrLed;
        }
    }

    return true;
}

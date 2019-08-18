#include "Frame.h"

unsigned Frame::setRangeToColor(unsigned startIdx, unsigned count, QColor color)
{
    std::fill(data.begin() + startIdx, data.begin() + startIdx + count, color);
    return count;
}

void Frame::clearFrame()
{ 
    std::fill(data.begin(), data.end(), Qt::transparent); 
}

void Frame::blendWithFrame(Frame &other)
{
    for (size_t i = 0; i < this->data.size(); i++)
    {
        auto &top = other.data[i];
        auto &base = this->data[i];

        const int factor_1 = top.alpha();
        if (factor_1 == 255)
        {
            this->data[i] = top;
        }
        else
        {
            const int factor_2 = base.alpha() * (255 - factor_1) / 255;
            int out_a = factor_1 + factor_2;

            if (out_a == 0)
            {
                this->data[i] = QColor(0, 0, 0, 0);
            }
            else
            {
                int out_r = (top.red()   * factor_1 + base.red()   * factor_2) / out_a;
                int out_g = (top.green() * factor_1 + base.green() * factor_2) / out_a;
                int out_b = (top.blue()  * factor_1 + base.blue()  * factor_2) / out_a;
                assert(out_r >= 0 && out_r <= 255);
                assert(out_g >= 0 && out_g <= 255);
                assert(out_b >= 0 && out_b <= 255);
                this->data[i] = QColor(out_r, out_g, out_b, out_a);
            }
        }
    }
}

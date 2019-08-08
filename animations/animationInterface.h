
#include "../helpers/frame.h"

class animationInterface
{
public:
    animationInterface();
    ~animationInterface();

    void draw(Frame &f) = 0;

};


#include <QApplication>
#include <QDebug>

#include <iostream>
#include <memory>

#include <Constants.h>
#include <Output.h>
#include <DebuggerWidget.h>
#include <Player.h>
#include <animations/AnimationConstantColor.h>
#include <animations/AnimationHighlightRotation.h>
#include <animations/AnimationRunningDot.h>
#include <animations/AnimationHighlightSparkling.h>
#include <animations/AnimationRainbow.h>
#include <animations/AnimationSegmentsFlashing.h>
#include <animations/AnimationUllas.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    qDebug() << "Hello from the Bitmovin Sign";
    
    Output output;
    DebuggerWidget debugger;
    AnimationList animationList({std::make_shared<AnimationHighlightRotation>()
                                //,std::make_shared<AnimationRunningDot>()
                                //,std::make_shared<AnimationConstantColor>()
                                ,std::make_shared<AnimationHighlightSparkling>()
                                ,std::make_shared<AnimationRainbow>()
                                ,std::make_shared<AnimationSegmentsFlashing>(BITMOVIN_BLUE, 20, 40)
                                ,std::make_shared<AnimationUllas>()
                                });
    Player player(animationList);

    player.set_debugger(&debugger);
    player.set_output(&output);

    debugger.show();
    
    return app.exec();
}

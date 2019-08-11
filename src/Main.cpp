
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

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    qDebug() << "Hello from the Bitmovin Sign";
    
    Output output;
    DebuggerWidget debugger;
    AnimationList animationList({std::make_shared<AnimationHighlightRotation>()
                                ,std::make_shared<AnimationRunningDot>()
                                ,std::make_shared<AnimationConstantColor>()
                                });
    Player player(animationList);

    player.set_debugger(&debugger);
    player.set_output(&output);

    debugger.show();
    
    return app.exec();
}

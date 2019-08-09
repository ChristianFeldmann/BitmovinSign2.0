
#include <QApplication>
#include <QDebug>

#include <iostream>

#include "helpers/frame.h"
#include "output/output.h"
#include "helpers/debugger_widget.h"
#include "helpers/player.h"
#include "animations/animation1.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    qDebug() << "Hello from the Bitmovin Sign";
    
    Output output;
    debugger_widget debugger;
    Player player;
    animation1 anim1;

    player.set_debugger(&debugger);
    player.set_output(&output);
    player.set_animation(&anim1);

    //auto animation = selectNewAnimation();
    // while (true)
    // {
    //     Frame f;

    //     //animation.draw(f);
    //     //debugger.show(f);
    //     //output.show(f);

    //     // sleep()
    // }
    debugger.show();
    
    return app.exec();
}

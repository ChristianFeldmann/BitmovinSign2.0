
#include <QApplication>
#include <QDebug>

#include <iostream>

#include "helpers/Frame.h"
#include "output/Output.h"
#include "helpers/DebuggerWidget.h"
#include "helpers/Player.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    qDebug() << "Hello from the Bitmovin Sign";
    
    Output output;
    DebuggerWidget debugger;
    Player player;

    player.set_debugger(&debugger);
    player.set_output(&output);

    debugger.show();
    
    return app.exec();
}

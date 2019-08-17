
#include <QApplication>
#include <QDebug>

#include <iostream>
#include <memory>

#include "Constants.h"
#include "DebuggerWidget.h"
#include "Player.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

#ifdef __arm__
    bool enableDebugger = false;
#else
    bool enableDebugger = true;
#endif

    if (argc == 2)
    {
        std::string arg = std::string(argv[1]);
        if (arg == "nodebug")
            enableDebugger = false;
        if (arg == "debug")
            enableDebugger = true;
    }
    
    qDebug() << "Hello from the Bitmovin Sign";
    
    Player player;

    std::unique_ptr<DebuggerWidget> debugger;
    if (enableDebugger)
    {
        debugger.reset(new DebuggerWidget);
    }
    player.set_debugger(debugger.get());

    if (debugger)
    {
        debugger->show();
    }
    
    return app.exec();
}

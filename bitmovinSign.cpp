
#include <QApplication>

#include "helpers/frame.h"
#include "helpers/debugger_widget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    debugger_widget debugger;
    debugger.show();

    //auto animation = selectNewAnimation();
    // while (true)
    // {
    //     Frame f;

    //     //animation.draw(f);
    //     //debugger.show(f);
    //     //output.show(f);

    //     // sleep()
    // }
    
    return app.exec();
}
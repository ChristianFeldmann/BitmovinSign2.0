
#include <QApplication>
#include <QDebug>

#include <iostream>

#include "helpers/frame.h"
#include "output/output.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    qDebug() << "Hello from the Bitmovin Sign";
    
    Output o;

    //auto animation = selectNewAnimation();
    while (true)
    {
        Frame f;

        //animation.draw(f);
        //debugger.show(f);
        //output.show(f);

        // sleep()
    }
    
}

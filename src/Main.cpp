
#include <QCoreApplication>
#include <QDebug>

#include <iostream>
#include <memory>

#include "common/Constants.h"
#include "common/Player.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    qDebug() << "Hello from the Bitmovin Sign Demon";
    
    Player player;
    player.enableAnimationSwitch();

    qDebug() << "Trying to load default playlist file Default.singPlaylist";
    if (!player.loadPlaylistFile("Default.signPlaylist"))
    {
        qDebug() << "Error loading default playlist file Default.singPlaylist";
        qDebug() << "Trying to create default playlist";
        if (!player.createDefaultPlaylist())
            qDebug() << "Error creating default playlist";
    }
    player.play();
    
    return app.exec();
}

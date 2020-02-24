
#include <QApplication>
#include <QDebug>

#include <iostream>
#include <memory>

#include "Constants.h"
#include "DebuggerMainWindow.h"
#include "Player.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    enum class Mode
    { 
        SignOnly,
        OutputView,
        AnimationEditor
    };

#ifdef __arm__
    Mode mode = Mode::SignOnly;
#else
    Mode mode = Mode::OutputView;
#endif

    if (argc == 2)
    {
        std::string arg = std::string(argv[1]);
        if (arg == "Sign")
            mode = Mode::SignOnly;
        if (arg == "Output")
            mode = Mode::OutputView;
        if (arg == "Editor")
            mode = Mode::AnimationEditor;
    }
    
    qDebug() << "Hello from the Bitmovin Sign";
    qDebug() << "Options:";
    qDebug() << "  Sign:   Only show animations on the sign (default on arm)";
    qDebug() << "  Output: Show the output also in a debugger window (default on non arm)";
    qDebug() << "  Editor: Show the animation editor";
    
    Player player;

    std::unique_ptr<DebuggerMainWindow> editor;
    if (mode == Mode::AnimationEditor)
    {
        editor.reset(new DebuggerMainWindow(&player));
        editor->show();
    }
    else
    {
        player.enableAnimationSwitch(10);
    }

    std::unique_ptr<DebuggerWidget> output;
    if (mode == Mode::OutputView)
    {
        output.reset(new DebuggerWidget(DebuggerWidget::DrawMode::OutputOnly));
        QObject::connect(&player, &Player::updateDebugger, output.get(), &DebuggerWidget::draw);
        output->resize(500, 500);
        output->show();
    }

    if (mode != Mode::AnimationEditor)
    {
        qDebug() << "Trying to load default playlist file Default.singPlaylist";
        if (!player.loadPlaylistFile("Default.signPlaylist"))
        {
            qDebug() << "Error loading default playlist file Default.singPlaylist";
            qDebug() << "Trying to create default playlist";
            if (!player.createDefaultPlaylist())
                qDebug() << "Error creating default playlist";
        }
    }
    
    return app.exec();
}

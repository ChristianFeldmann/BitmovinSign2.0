
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

    std::unique_ptr<DebuggerWidget> output;
    if (mode == Mode::OutputView)
    {
        output.reset(new DebuggerWidget(DebuggerWidget::DrawMode::OutputOnly));
        QObject::connect(&player, &Player::updateDebugger, output.get(), &DebuggerWidget::draw);
        output->show();
    }

    if (mode != Mode::AnimationEditor)
    {
        if (!player.createDefaultPlaylist())
            qDebug() << "Error creating default playlist";
        // if (!player.loadPlaylistFile("Default.signPlaylist"))
        // {
        //     player.createDefaultPlaylist();
        // }
    }
    
    return app.exec();
}

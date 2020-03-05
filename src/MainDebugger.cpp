#include <QApplication>
#include <QDebug>

#include <iostream>
#include <memory>

#include "common/Constants.h"
#include "debugger/DebuggerMainWindow.h"
#include "common/Player.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Q_INIT_RESOURCE(resources);
    
    enum class Mode
    { 
        SignOnly,
        OutputView,
        AnimationEditor
    };

#ifdef __arm__
    Mode mode = Mode::OutputView;
#else
    Mode mode = Mode::AnimationEditor;
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
    qDebug() << "  Sign:   Only show animations on the sign";
    qDebug() << "  Output: Show the output also in a debugger window (default on arm)";
    qDebug() << "  Editor: Show the animation editor (default on non arm)";
    
    Player player;

    std::unique_ptr<DebuggerMainWindow> editor;
    if (mode == Mode::AnimationEditor)
    {
        editor.reset(new DebuggerMainWindow(&player));
        editor->show();
    }
    else
    {
        player.enableAnimationSwitch();
    }

    std::unique_ptr<DebuggerWidget> output;
    if (mode == Mode::OutputView)
    {
        output.reset(new DebuggerWidget());
        output->setDrawMode(DebuggerWidget::DrawMode::OutputOnly);
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
        player.play(true);
    }
    
    return app.exec();
}

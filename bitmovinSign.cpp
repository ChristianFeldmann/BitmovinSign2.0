
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto animation = selectNewAnimation();
    while (true)
    {
        frame f;

        animation.draw(f);

        debugger.show(f);
        output.show(f);


    }
    
}
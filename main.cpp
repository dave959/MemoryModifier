#include "MemoryModifier.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MemoryModifier w;
    w.show();

    QIcon icon;
    icon.addFile(":/icon.jpg");
    w.setWindowIcon(icon);
    return a.exec();
}

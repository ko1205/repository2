#include "timeline.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    timeline w;
    w.show();

    return a.exec();
}

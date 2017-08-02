#include "timeline.h"
#include <QApplication>
#include <QScrollBar>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    timeline w;
    w.show();
    return a.exec();
}

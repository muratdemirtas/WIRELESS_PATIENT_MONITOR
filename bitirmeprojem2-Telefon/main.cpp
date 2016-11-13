#include "anaekran.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    anaekran w;
//  w.showMaximized();
    w.show();

    return a.exec();
}

#include "anaekran.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.addLibraryPath(QCoreApplication::applicationDirPath()+"/plugins");
    anaekran w;
 w.showMaximized();
    w.show();

    return a.exec();
}

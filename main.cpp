#include "mainmenu.h"
#include "sessionlogwindow.h"
#include "pcwindow.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PCWindow w;
    w.show();
    return a.exec();
}

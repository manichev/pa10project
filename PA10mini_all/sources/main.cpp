#include "pax_prototype.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PAX_Prototype w;
    w.show();
    return a.exec();
}

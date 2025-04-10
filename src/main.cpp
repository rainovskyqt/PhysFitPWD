#include <QApplication>
#include "login/formlogin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FormLogin l;
    l.show();
    return a.exec();
}

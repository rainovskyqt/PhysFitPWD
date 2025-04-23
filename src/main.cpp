#include <QApplication>
#include <database/database.h>
#include "login/formlogin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DataBase::make("config.db");

    FormLogin l;
    l.show();
    return a.exec();
}

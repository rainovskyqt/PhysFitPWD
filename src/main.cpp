#include <QApplication>
#include <database/baseworker.h>
#include "login/formlogin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    BaseWorker::get()->init("config.db");

    FormLogin l;
    l.show();
    return a.exec();
}

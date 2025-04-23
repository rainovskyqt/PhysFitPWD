#include "settings.h"

Q_GLOBAL_STATIC(Settings, global_inst)

Settings::Settings(){}

Settings *Settings::take()
{
    return global_inst();
}

QString Settings::dbHost()
{
    return get<QString>("dbHost", "127.0.0.1");
}

void Settings::setDbHost(QString host)
{
    set("dbHost", host);
}

int Settings::dbPort()
{
    return get<int>("dbPort", 3306);
}

void Settings::setDbPort(int port)
{
    set("dbPort", port);
}

QString Settings::lastName()
{
    return get<QString>("lastName", "");
}

void Settings::setLastName(QString lastName)
{
    set("lastName", lastName);
}

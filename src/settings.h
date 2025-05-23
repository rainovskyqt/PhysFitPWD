#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QObject>

class Settings : public QSettings
{
    Q_OBJECT

public:
    Settings();
    static Settings *take();
    ~Settings() {}

    QString dbHost();
    void setDbHost(QString host);

    int dbPort();
    void setDbPort(int port);

    QString lastName();
    void setLastName(QString lastName);

private:
    static Settings *settings;

    template<typename  T>
    T get(const QString &key, const T &defValue = {}){
        QSettings s("settings.ini", QSettings::IniFormat);
        QVariant val = s.value(key, defValue);
        return val.value<T>();
    }

    template<typename  T>
    void set(const QString &key, const T &val){
        QSettings s("settings.ini", QSettings::IniFormat);
        s.setValue(key, val);
    }

};


#endif // SETTINGS_H

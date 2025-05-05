#ifndef EXAMINEEMANAGER_H
#define EXAMINEEMANAGER_H

#include <QObject>

class ExamineeManager : public QObject
{
    Q_OBJECT
public:
    explicit ExamineeManager(QObject *parent = nullptr);

    QStringList getDepartments();

private:
};

#endif // EXAMINEEMANAGER_H

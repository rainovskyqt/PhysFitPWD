#ifndef EXAMINEEMANAGER_H
#define EXAMINEEMANAGER_H

#include <QObject>
#include <QVector>

class Department;

class ExamineeManager : public QObject
{
    Q_OBJECT
public:
    explicit ExamineeManager(QObject *parent = nullptr);

    QVector<Department*> getDepartments();

private:
};

#endif // EXAMINEEMANAGER_H

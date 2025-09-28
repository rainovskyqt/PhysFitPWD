#ifndef EXAMINEEMANAGER_H
#define EXAMINEEMANAGER_H

#include <QMultiHash>
#include <QObject>
#include <QVector>

class Department;
class Examinee;

class ExamineeManager : public QObject
{
    Q_OBJECT
public:
    explicit ExamineeManager(QObject *parent = nullptr);

//    QVector<Department*> getDepartments();
    Examinee *getExaminee(int id);
    void saveExaminee(Examinee *e);
    QMultiHash<QString, QPair<QString, int> > examineeList(int dep = 0);

private:
};

#endif // EXAMINEEMANAGER_H

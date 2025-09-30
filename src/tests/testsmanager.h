#ifndef TESTSMANAGER_H
#define TESTSMANAGER_H

#include "testexercise.h"

#include <QObject>

class Exercise;
class Test;

class TestsManager : public QObject
{
    Q_OBJECT
public:
    explicit TestsManager(QObject *parent = nullptr);

    void saveExercise(Exercise *e);
    Exercise* exercise(int id);
    void deleteExercise(int id);
    QList<Exercise*> loadExercises();
    Test* test(int id);
    QList<Test*> loadTests();
    void saveTest(Test* t);
    void deleteTest(int id);
    void editTestExercise(Test* t);
    void saveTestExercise(TestExercise* t);
    void deleteTestExercise(QList<int> deleted);
    void parceTestExercise(QString grade, Test* t);

signals:
};

#endif // TESTSMANAGER_H

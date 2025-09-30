#ifndef TESTSMANAGER_H
#define TESTSMANAGER_H

#include <QObject>

class Exercise;

class TestsManager : public QObject
{
    Q_OBJECT
public:
    explicit TestsManager(QObject *parent = nullptr);

    void saveExercise(Exercise *e);
    Exercise* exercise(int id);
    void deleteExercise(int id);
    QList<Exercise*> loadExercises();

signals:
};

#endif // TESTSMANAGER_H

#ifndef TESTEXERCISE_H
#define TESTEXERCISE_H

#include <QObject>

class TestExercise : public QObject
{
    Q_OBJECT
public:
    explicit TestExercise(QObject *parent = nullptr);

    int id() const;
    void setId(int newId);
    int exerciseId() const;
    void setExerciseId(int newExerciseId);
    QString exerciseName() const;
    void setExerciseName(QString newExerciseName);
    QString grades() const;
    void setGrades(const QString &newGrades);

    int testId() const;
    void setTestId(int newTestId);

signals:

private:
    int m_id;
    int m_testId;
    int m_exerciseId;
    QString m_exerciseName;
    QString m_grades;
};

#endif // TESTEXERCISE_H

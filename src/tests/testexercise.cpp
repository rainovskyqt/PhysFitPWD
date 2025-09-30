#include "testexercise.h"

TestExercise::TestExercise(QObject *parent)
    : QObject{parent}
{

}

int TestExercise::id() const
{
    return m_id;
}

void TestExercise::setId(int newId)
{
    m_id = newId;
}

int TestExercise::exerciseId() const
{
    return m_exerciseId;
}

void TestExercise::setExerciseId(int newExerciseId)
{
    m_exerciseId = newExerciseId;
}

QString TestExercise::exerciseName() const
{
    return m_exerciseName;
}

void TestExercise::setExerciseName(QString newExerciseName)
{
    m_exerciseName = newExerciseName;
}

QString TestExercise::grades() const
{
    return m_grades;
}

void TestExercise::setGrades(const QString &newGrades)
{
    m_grades = newGrades;
}

int TestExercise::testId() const
{
    return m_testId;
}

void TestExercise::setTestId(int newTestId)
{
    m_testId = newTestId;
}

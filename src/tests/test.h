#ifndef TEST_H
#define TEST_H

#include "testexercise.h"

#include <QObject>

class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject *parent = nullptr);

    int id() const;
    void setId(int newId);
    QString name() const;
    void setName(const QString &newName);
    int subgroup() const;
    void setSubgroup(int newSubgroup);
    int ageGroup() const;
    void setAgeGroup(int newAgeGroup);

    QList<TestExercise *> exercises() const;
    void addExercise(TestExercise *e);
    QString subgroupName();
    QString ageGroupName();

    QList<int> deleted() const;
    void setDeleted(const QList<int> &newDeleted);

signals:

private:
    int m_id;
    QString m_name;
    int m_subgroup;
    int m_ageGroup;
    QString m_subgroupName;
    QString m_ageGroupName;
    QList<TestExercise*> m_exercises;
    QList<int> m_deleted;
};

#endif // TEST_H

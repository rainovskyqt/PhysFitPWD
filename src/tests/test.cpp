#include "test.h"

#include <dictionary/dictionary.h>
#include <dictionary/dictionarymanager.h>

Test::Test(QObject *parent)
    : QObject{parent}
{}

int Test::id() const
{
    return m_id;
}

void Test::setId(int newId)
{
    m_id = newId;
}

QString Test::name() const
{
    return m_name;
}

void Test::setName(const QString &newName)
{
    m_name = newName;
}

int Test::subgroup() const
{
    return m_subgroup;
}

void Test::setSubgroup(int newSubgroup)
{
    m_subgroup = newSubgroup;
    auto dm = new DictionaryManager(this);
    auto d = dm->getDictionary(Dictionary::Type::SubGroups);
    m_subgroupName = d->value(m_subgroup);
    dm->deleteLater();
}

int Test::ageGroup() const
{
    return m_ageGroup;
}

void Test::setAgeGroup(int newAgeGroup)
{
    m_ageGroup = newAgeGroup;
    auto dm = new DictionaryManager(this);
    auto d = dm->getDictionary(Dictionary::Type::AgeGroups);
    m_ageGroupName = d->value(m_ageGroup);
    dm->deleteLater();
}

QList<TestExercise *> Test::exercises() const
{
    return m_exercises;
}

void Test::addExercise(TestExercise *e)
{
    e->setTestId(m_id);
    m_exercises.append(e);
}

QString Test::subgroupName()
{
    return m_subgroupName;
}

QString Test::ageGroupName()
{
    return m_ageGroupName;
}

QList<int> Test::deleted() const
{
    return m_deleted;
}

void Test::setDeleted(const QList<int> &newDeleted)
{
    m_deleted = newDeleted;
}

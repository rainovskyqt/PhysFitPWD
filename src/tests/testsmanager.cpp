#include "exercise.h"
#include "test.h"
#include "testsmanager.h"

#include <database/baseworker.h>

#include <QVariant>

TestsManager::TestsManager(QObject *parent)
    : QObject{parent}
{}

void TestsManager::saveExercise(Exercise *e)
{
    QString insert = QString("INSERT INTO exercise (name, units, direction) "
                             "VALUES (:name, :units, :direction)");
    QString update = QString("UPDATE exercise SET name = :name, units = :units, direction = :direction "
                             "WHERE id = :id"
                             );

    QMap<QString, QVariant>params;
    params.insert(":id", QVariant(e->id()));
    params.insert(":name", QVariant(e->name()));
    params.insert(":units", QVariant(e->units()));
    params.insert(":direction", QVariant(e->direction()));

    if(e->id()){
        BaseWorker::get()->updateOrDelete(update, params);
    } else {
        BaseWorker::get()->insert(insert, params);
    }
}

Exercise *TestsManager::exercise(int id)
{
    QString queryString = QString("SELECT id, name, units, direction "
                                  "FROM exercise "
                                  "WHERE id = :id");

    QMap<QString, QVariant>params;
    params.insert(":id", QVariant(id));

    Exercise *e = new Exercise();

    auto *q = BaseWorker::get()->select(queryString, params);

    if (q->next()) {
        e->setId(q->value("id").toInt());
        e->setName(q->value("name").toString());
        e->setUnits(q->value("units").toInt());
        e->setDirection(q->value("direction").toInt());
    }

    delete q;
    return e;
}

void TestsManager::deleteExercise(int id)
{
    QString del = QString("DELETE FROM exercise "
                          "WHERE id = :id"
                          );

    QMap<QString, QVariant>params;
    params.insert(":id", QVariant(id));

    BaseWorker::get()->updateOrDelete(del, params);
}

QList<Exercise *> TestsManager::loadExercises()
{
    QList<Exercise *> l;

    QString queryString = QString("SELECT id, name, units, direction "
                                  "FROM exercise "
                                  "ORDER BY name");

    auto *q = BaseWorker::get()->select(queryString);

    while (q->next()) {
        auto e = new Exercise();
        e->setId(q->value("id").toInt());
        e->setName(q->value("name").toString());
        e->setUnits(q->value("units").toInt());
        e->setDirection(q->value("direction").toInt());
        l.append(e);
    }

    return l;
}

Test *TestsManager::test(int id)
{
    QString queryString = QString("SELECT T.id, T.name, T.age_group, T.subgroup, "
                                  "GROUP_CONCAT(TE.id || '|' || TE.exercise || '|' || E.name || '|' || TE.grades, '||') AS grades "
                                  "FROM tests T "
                                  "LEFT JOIN test_exercises TE ON TE.test = T.id "
                                  "LEFT JOIN exercise E ON TE.exercise = E.id "
                                  "WHERE T.id = :id");

    QMap<QString, QVariant>params;
    params.insert(":id", QVariant(id));

    auto *t = new Test();

    auto *q = BaseWorker::get()->select(queryString, params);

    if (q->next()) {
        t->setId(q->value("id").toInt());
        t->setName(q->value("name").toString());
        t->setSubgroup(q->value("subgroup").toInt());
        t->setAgeGroup(q->value("age_group").toInt());
        parceTestExercise(q->value("grades").toString(), t);
    }

    delete q;
    return t;
}

QList<Test *> TestsManager::loadTests()
{
    QList<Test *> l;

    QString queryString = QString("SELECT id, name, age_group, subgroup "
                                  "FROM tests "
                                  "ORDER BY name");

    auto *q = BaseWorker::get()->select(queryString);

    while (q->next()) {
        auto t = new Test();
        t->setId(q->value("id").toInt());
        t->setName(q->value("name").toString());
        t->setSubgroup(q->value("subgroup").toInt());
        t->setAgeGroup(q->value("age_group").toInt());
        l.append(t);
    }

    return l;
}

void TestsManager::saveTest(Test *t)
{
    QString insert = QString("INSERT INTO tests (name, subgroup, age_group) "
                             "VALUES (:name, :subgroup, :age_group)");
    QString update = QString("UPDATE tests SET name = :name, subgroup = :subgroup, age_group = :age_group "
                             "WHERE id = :id"
                             );

    QMap<QString, QVariant>params;
    params.insert(":id", QVariant(t->id()));
    params.insert(":name", QVariant(t->name()));
    params.insert(":subgroup", QVariant(t->subgroup()));
    params.insert(":age_group", QVariant(t->ageGroup()));

    if(t->id()){
        BaseWorker::get()->updateOrDelete(update, params);
    } else {
        int id = BaseWorker::get()->insert(insert, params);
        t->setId(id);
    }
    editTestExercise(t);
}

void TestsManager::editTestExercise(Test *t)
{
    auto exercise = t->exercises();
    for(auto te : qAsConst(exercise)){
        te->setTestId(t->id());
        saveTestExercise(te);
    }
    deleteTestExercise(t->deleted());
}

void TestsManager::saveTestExercise(TestExercise *t)
{
    QString insert = QString("INSERT INTO test_exercises (test, exercise, grades) "
                             "VALUES (:test, :exercise, :grades)");
    QString update = QString("UPDATE test_exercises SET test = :test, exercise = :exercise, grades = :grades "
                             "WHERE id = :id");
    QMap<QString, QVariant>params;
    params.insert(":id", QVariant(t->id()));
    params.insert(":test", QVariant(t->testId()));
    params.insert(":exercise", QVariant(t->exerciseId()));
    params.insert(":grades", QVariant(t->grades()));
    if(t->id()){
        BaseWorker::get()->updateOrDelete(update, params);
    } else {
        int id = BaseWorker::get()->insert(insert, params);
        t->setId(id);
    }
}

void TestsManager::deleteTestExercise(QList<int> deleted)
{
    QString del = QString("DELETE FROM test_exercises "
                          "WHERE id IN (:id)"
                          );
    QStringList ids;
    for(auto id : deleted)
        ids.append(QString::number(id));
    QMap<QString, QVariant>params;
    params.insert(":id", QVariant(ids.join(",")));

    BaseWorker::get()->updateOrDelete(del, params);
}

void TestsManager::parceTestExercise(QString grade, Test *t)
{
    if(grade.isEmpty())
        return;
    QStringList execises = grade.split("||");
    for(int i = 0; i < execises.count(); ++i){
        QStringList grades = execises.at(i).split("|");
        auto te = new TestExercise();
        te->setId(grades.at(0).toInt());
        te->setExerciseId(grades.at(1).toInt());
        te->setExerciseName(grades.at(2));
        te->setGrades(grades.at(3));
        t->addExercise(te);
    }
}

void TestsManager::deleteTest(int id)
{
    QString del = QString("DELETE FROM tests "
                          "WHERE id = :id"
                          );

    QMap<QString, QVariant>params;
    params.insert(":id", QVariant(id));

    BaseWorker::get()->updateOrDelete(del, params);
}



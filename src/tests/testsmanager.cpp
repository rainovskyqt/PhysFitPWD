#include "exercise.h"
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
                                  "FROM exercise ");

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

#include "examineemanager.h"

#include "database/baseworker.h"
#include <QVariant>
#include "department.h"

ExamineeManager::ExamineeManager(QObject *parent) : QObject(parent)
{
}

QVector<Department*> ExamineeManager::getDepartments()
{
    QString queryString = QString("SELECT id, name "
                                  "FROM departments "
                                  "ORDER BY name");

    auto *q = BaseWorker::get()->select(queryString);
    QVector<Department*> deps;

    while (q->next()) {
       deps.append(new Department(q->value("id").toInt(), q->value("name").toString()));
    }

    delete q;

    return deps;
}


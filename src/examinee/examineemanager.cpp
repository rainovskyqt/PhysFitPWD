#include "examineemanager.h"

#include "database/baseworker.h"
#include <QVariant>

ExamineeManager::ExamineeManager(QObject *parent) : QObject(parent)
{
}

QStringList ExamineeManager::getDepartments()
{
    QString queryString = QString("SELECT id, name "
                                  "FROM departments "
                                  "ORDER BY name");

    auto *q = BaseWorker::get()->select(queryString);
    QStringList deps;

    while (q->next()) {
       deps.append(q->value("name").toString());
    }

    delete q;

    return deps;
}

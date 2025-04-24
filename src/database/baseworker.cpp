#include "baseworker.h"

#include <QVariant>
#include <QSqlError>
#include <QDebug>
#include <QFile>

#include "database/tablecreator.h"

Q_GLOBAL_STATIC(BaseWorker, staticInst)

BaseWorker::BaseWorker(QObject *parent)
    : QObject{parent}
{
}

void BaseWorker::init(QString baseName)
{
    m_base = QSqlDatabase::addDatabase("QSQLITE");
    m_base.setDatabaseName(baseName);

    if(m_base.lastError().isValid()){
        qCritical() << m_base.lastError().text();
        return;
    }

    bool isNew = !checkBasefile(baseName);

    auto creator = new TableCreator();
    creator->createTables(&m_base);

    if(isNew)
        creator->addDefaultData(&m_base);

    m_base.close();
}

BaseWorker *BaseWorker::get()
{
    return staticInst;
}



bool BaseWorker::checkBasefile(const QString &fileName)
{
    return QFile(fileName).exists();
}

QSqlQuery *BaseWorker::select(QString queryText, QMap<QString, QVariant> params)
{
    return executeQuery(queryText, params);
}

int BaseWorker::insert(QString queryText, QMap<QString, QVariant> params)
{
    QSqlQuery *query = executeQuery(queryText, params);
    int newId = query->lastInsertId().toInt();
    delete query;
    return newId;
}

void BaseWorker::updateOrDelete(QString queryText, QMap<QString, QVariant> params)
{
    delete executeQuery(queryText, params);
}

QSqlQuery *BaseWorker::executeQuery(const QString &queryText, const QMap<QString, QVariant> &params)
{
    if (!m_base.isOpen()) {
        if(!m_base.open())
            qCritical() << m_base.lastError().text();
    }

    QSqlQuery *query = new QSqlQuery(m_base);

    query->prepare(queryText);

    for(auto it = params.begin(); it != params.end(); ++it){
        query->bindValue(it.key(), it.value());
    }

    query->exec();

    if(query->lastError().isValid()) {
        qCritical() << "executeQuery: " << query->lastError().text();
    }

    return query;
}

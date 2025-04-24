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

Dictionary *BaseWorker::getDictionary(Dictionary::Type type)
{
    QString table = getDictonaryTable(type);

    auto *dict = new Dictionary();

    QString queryString = QString("SELECT id, name, orderPlace "
                                  "FROM %1 "
                                  "ORDER BY orderPlace").arg(table);

    auto *q = select(queryString);

    while (q->next()) {
        dict->addVal(q->value("id").toInt(), q->value("name").toString());
    }

    delete q;

    return dict;
}

void BaseWorker::addDictory(Dictionary::Type type, QString name)
{
    QString table = getDictonaryTable(type);

    QString queryString = QString("INSERT INTO %1(name, orderPlace) "
                                  "VALUES (:name, (SELECT MAX(orderPlace) + 1 FROM %1))").arg(table);

    QMap<QString, QVariant>params;
    params.insert(":name", QVariant(name));

    insert(queryString, params);
}

void BaseWorker::editDictory(Dictionary::Type type, int id, QString name, int orderPlace)
{
    QString table = getDictonaryTable(type);

    QString queryString = QString("UPDATE %1 "
                                  "SET name = :name ,"
                                  "orderPlace = :orderPlace "
                                  "WHERE id = :id").arg(table);

    QMap<QString, QVariant>params;
    params.insert(":name", QVariant(name));
    params.insert(":orderPlace", QVariant(orderPlace));
    params.insert(":id", QVariant(id));

    updateOrDelete(queryString, params);
}

void BaseWorker::deleteDictory(Dictionary::Type type, int id)
{
    QString table = getDictonaryTable(type);

    QString queryString = QString("DELETE FROM %1 "
                                  "WHERE id = :id").arg(table);

    QMap<QString, QVariant>params;
    params.insert(":id", QVariant(id));

    updateOrderPlace(type, id);

    updateOrDelete(queryString, params);
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

QString BaseWorker::getDictonaryTable(Dictionary::Type type)
{
    switch (type) {
    case Dictionary::Type::Rangs:
        return "rangs";
    case Dictionary::Type::AgeGroups:
        return "age_groups";
    case Dictionary::Type::Groups:
        return "groups";
    case Dictionary::Type::SubGroups:
        return "sub_groups";
    case Dictionary::Type::Clearance:
        return "doctor_clearance";
    case Dictionary::Type::Diagnosis:
        return "diagnosis";
    }

    return "";
}

void BaseWorker::updateOrderPlace(Dictionary::Type type, int id)
{
    QString table = getDictonaryTable(type);

    QString queryString = QString("UPDATE %1 "
                                  "SET orderPlace = orderPlace - 1 "
                                  "WHERE orderPlace > ("
                                  "SELECT orderPlace "
                                  "FROM %1 "
                                  "WHERE id = :id)").arg(table);
    QMap<QString, QVariant>params;
    params.insert(":id", QVariant(id));

    updateOrDelete(queryString, params);
}

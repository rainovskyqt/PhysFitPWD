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

    // m_base.close();
}

BaseWorker *BaseWorker::get()
{
    return staticInst;
}

Dictionary *BaseWorker::getDictionary(Dictionary::Type type)
{
    QString table = "";

    switch (type) {
    case Dictionary::Type::Rangs:
        table = "rangs";
        break;
    case Dictionary::Type::AgeGroups:
        table = "age_groups";
        break;
    case Dictionary::Type::Groups:
        table = "groups";
        break;
    case Dictionary::Type::SubGroups:
        table = "sub_groups";
        break;
    case Dictionary::Type::Clearance:
        table = "doctor_clearance";
        break;
    case Dictionary::Type::Diagnosis:
        table = "diagnosis";
        break;
    }

    auto *dict = new Dictionary();

    QString queryString = QString("SELECT id, name, orderPlace "
                                  "FROM %1 "
                                  "ORDER BY orderPlace").arg(table);

    // QMap<QString, QVariant>params;
    // params.insert(":controller_id", QVariant(cncId));

    // if(base == nullptr)
    //     base = MainProvider::get()->settingsBase();

    auto *q = select(queryString);

    while (q->next()) {
        dict->addVal(q->value("id").toInt(), q->value("name").toString());
    }

    delete q;

    return dict;
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

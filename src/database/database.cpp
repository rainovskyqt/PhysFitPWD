#include "database.h"
#include "tablecreator.h"

#include <QDebug>
#include <QFile>
#include <QSqlDatabase>

DataBase::DataBase(const QString &connectionName, QObject *parent)
    : QObject{parent}
{
    m_connectionName = connectionName;
}

DataBase::~DataBase()
{
    if(QSqlDatabase::database(m_connectionName).isOpen())
        QSqlDatabase::database(m_connectionName).close();

    QSqlDatabase::removeDatabase(m_connectionName);
}

DataBase* DataBase::make(const QString &baseName, const QString &connectionName)
{
    QSqlDatabase base = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    base.setDatabaseName(baseName);

    if(base.lastError().isValid()){
        qCritical() << base.lastError().text();
        return nullptr;
    }

    bool isNew = !checkBasefile(baseName);

    QScopedPointer<DataBase> setting(new DataBase(connectionName));

    auto creator = new TableCreator();
    creator->createTables(&base);

    if(isNew)
        creator->addDefaultData(&base);

    // setting->createMissingTables();
    // setting->updateTables();

    // if(!defaultData)
    //     setting->clearBase(&base);

    // base.close();

    return setting.take();
}

bool DataBase::checkBasefile(const QString &fileName)
{
    return QFile(fileName).exists();
}

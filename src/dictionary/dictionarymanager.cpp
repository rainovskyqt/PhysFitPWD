#include "dictionarymanager.h"

#include <QVariant>
#include <database/baseworker.h>

DictionaryManager::DictionaryManager(QObject *parent)
    : QObject{parent}
{
}

Dictionary *DictionaryManager::getDictionary(Dictionary::Type type)
{
    QString table = getDictonaryTable(type);

    auto *dict = new Dictionary();

    QString queryString = QString("SELECT id, name, orderPlace "
                                  "FROM %1 "
                                  "ORDER BY orderPlace").arg(table);

    auto *q = BaseWorker::get()->select(queryString);

    while (q->next()) {
        dict->addVal(q->value("id").toInt(), q->value("name").toString());
    }

    delete q;

    return dict;
}

void DictionaryManager::addDictory(Dictionary::Type type, QString name)
{
    QString table = getDictonaryTable(type);

    QString queryString = QString("INSERT INTO %1(name, orderPlace) "
                                  "VALUES (:name, (SELECT MAX(orderPlace) + 1 FROM %1))").arg(table);

    QMap<QString, QVariant>params;
    params.insert(":name", QVariant(name));

    BaseWorker::get()->insert(queryString, params);
}

void DictionaryManager::editDictory(Dictionary::Type type, int id, QString name, int orderPlace)
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

    BaseWorker::get()->updateOrDelete(queryString, params);
}

void DictionaryManager::deleteDictory(Dictionary::Type type, int id)
{
    QString table = getDictonaryTable(type);

    QString queryString = QString("DELETE FROM %1 "
                                  "WHERE id = :id").arg(table);

    QMap<QString, QVariant>params;
    params.insert(":id", QVariant(id));

    updateOrderPlace(type, id);

    BaseWorker::get()->updateOrDelete(queryString, params);
}

void DictionaryManager::swapPlace(Dictionary::Type type, int idFirst, int idSecond)
{
    int firstPlace = getOrderPlace(type, idFirst);
    int secondPlace = getOrderPlace(type, idSecond);

    QString table = getDictonaryTable(type);

    QString queryString = QString("UPDATE %1 SET orderPlace = :orderPlace WHERE id = :id").arg(table);

    QMap<QString, QVariant>params;
    params.insert(":id", QVariant(idFirst));
    params.insert(":orderPlace", QVariant(secondPlace));
    BaseWorker::get()->updateOrDelete(queryString, params);

    params.insert(":id", QVariant(idSecond));
    params.insert(":orderPlace", QVariant(firstPlace));
    BaseWorker::get()->updateOrDelete(queryString, params);
}

QString DictionaryManager::getDictonaryTable(Dictionary::Type type)
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

void DictionaryManager::updateOrderPlace(Dictionary::Type type, int id)
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

    BaseWorker::get()->updateOrDelete(queryString, params);
}

int DictionaryManager::getOrderPlace(Dictionary::Type type, int id)
{
    QString table = getDictonaryTable(type);

    QString queryString = QString("SELECT orderPlace FROM %1 WHERE id = :id").arg(table);

    QMap<QString, QVariant>params;
    params.insert(":id", QVariant(id));

    auto q = BaseWorker::get()->select(queryString, params);
    q->next();
    return q->value("orderPlace").toInt();
}

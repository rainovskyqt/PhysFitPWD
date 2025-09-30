#include "dictionarymanager.h"

#include <QVariant>
#include <database/baseworker.h>

DictionaryManager::DictionaryManager(QObject *parent)
    : QObject{parent}
{
    m_humanName.insert(DType::Departments,"Войсковая чать");
    m_humanName.insert(DType::Rangs,"Звание");
    m_humanName.insert(DType::AgeGroups,"Возрастная группа");
    m_humanName.insert(DType::Groups,"Группа");
    m_humanName.insert(DType::SubGroups,"Подгруппа");
    m_humanName.insert(DType::Diagnosis,"Диагноз");
    m_humanName.insert(DType::Subdivision,"Подразделение");
}

Dictionary *DictionaryManager::getDictionary(DType type)
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

void DictionaryManager::addDictory(DType type, QString name)
{
    QString table = getDictonaryTable(type);

    QString queryString = QString("INSERT INTO %1(name, orderPlace) "
                                  "VALUES (:name, (SELECT MAX(orderPlace) + 1 FROM %1))").arg(table);

    QMap<QString, QVariant>params;
    params.insert(":name", QVariant(name));

    BaseWorker::get()->insert(queryString, params);
}

void DictionaryManager::editDictory(DType type, int id, QString name, int orderPlace)
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

void DictionaryManager::deleteDictory(DType type, int id)
{
    QString table = getDictonaryTable(type);

    QString queryString = QString("DELETE FROM %1 "
                                  "WHERE id = :id").arg(table);

    QMap<QString, QVariant>params;
    params.insert(":id", QVariant(id));

    updateOrderPlace(type, id);

    BaseWorker::get()->updateOrDelete(queryString, params);
}

void DictionaryManager::swapPlace(DType type, int idFirst, int idSecond)
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

QString DictionaryManager::humanName(DType type)
{
    return m_humanName.value(type, "");
}

void DictionaryManager::loadDictionary(DType type, QComboBox *box)
{
    auto mng = new DictionaryManager(this);
    auto dict = mng->getDictionary(type);
    auto const vals = dict->values();

    for(auto const &v : vals){
        box->addItem(v.second, v.first);
    }
}

QString DictionaryManager::getDictonaryTable(DType type)
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
    case Dictionary::Type::Diagnosis:
        return "diagnosis";
    case Dictionary::Type::Departments:
        return "departments";
    case Dictionary::Type::Subdivision:
        return "subdivision";
    case Dictionary::Type::ExerciseUnits:
        return "exercise_units";
    case Dictionary::Type::ExerciseDirection:
        return "exercise_direction";
    }

    return "";
}

void DictionaryManager::updateOrderPlace(DType type, int id)
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

int DictionaryManager::getOrderPlace(DType type, int id)
{
    QString table = getDictonaryTable(type);

    QString queryString = QString("SELECT orderPlace FROM %1 WHERE id = :id").arg(table);

    QMap<QString, QVariant>params;
    params.insert(":id", QVariant(id));

    auto q = BaseWorker::get()->select(queryString, params);
    q->next();
    return q->value("orderPlace").toInt();
}

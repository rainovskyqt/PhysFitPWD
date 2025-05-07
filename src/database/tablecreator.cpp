#include "tablecreator.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

TableCreator::TableCreator(QObject *parent)
    : QObject{parent}
{}

bool TableCreator::createTables(QSqlDatabase *db)
{
    if(!db->isOpen()){
        if(!db->open())
            return false;
    }

    auto tables = db->tables();

    createDictionary("rangs", db, tables);
    createDictionary("age_groups", db, tables);
    createDictionary("groups", db, tables);
    createDictionary("sub_groups", db, tables);
    createDictionary("doctor_clearance", db, tables);
    createDictionary("diagnosis", db, tables);
    createDictionary("departments", db, tables);

    //    createDepartments(db, tables);
    createExaminee(db, tables);

    db->close();

    return true;
}

bool TableCreator::addDefaultData(QSqlDatabase *db)
{
    if(!db->isOpen()){
        if(!db->open())
            return false;
    }

    addDefaultDictionary(db);

    db->close();

    return true;
}

bool TableCreator::createTable(const QString &name, const QStringList &params,
                               QSqlDatabase *db, const QStringList &tables) {
    if (tables.contains(name))
        return false;

    QSqlQuery query(*db);
    QString queryString = QString("CREATE TABLE IF NOT EXISTS %1 ( %2 )").arg(name, params.join(", "));
    query.exec(queryString);

    if(query.lastError().isValid()){
        qCritical() << query.lastError().text();
        return false;
    }

    return true;
}

bool TableCreator::createDictionary(const QString &name, QSqlDatabase *db, const QStringList &tables)
{
    createTable(name, {"id INTEGER PRIMARY KEY AUTOINCREMENT",
                       "name VARCHAR(255)",
                       "orderPlace INTEGER"},
                db, tables);

    return true;
}

void TableCreator::addDefaultDictionary(QSqlDatabase *db)
{
    QStringList queryStrings;
    queryStrings.append(QString("INSERT INTO rangs(name, orderPlace) VALUES %2").arg(dictionaryParams(rangs())));
    queryStrings.append(QString("INSERT INTO age_groups(name, orderPlace) VALUES %2").arg(dictionaryParams(ageGroups())));
    queryStrings.append(QString("INSERT INTO groups(name, orderPlace) VALUES %2").arg(dictionaryParams(groups())));
    queryStrings.append(QString("INSERT INTO sub_groups(name, orderPlace) VALUES %2").arg(dictionaryParams(subGroups())));
    queryStrings.append(QString("INSERT INTO doctor_clearance(name, orderPlace) VALUES %2").arg(dictionaryParams(clearance())));
    queryStrings.append(QString("INSERT INTO diagnosis(name, orderPlace) VALUES %2").arg(dictionaryParams(diagnosis())));

    QSqlQuery query(*db);
    for(const auto &q : qAsConst(queryStrings))
        query.exec(q);
}

QString TableCreator::dictionaryParams(const QStringList data)
{
    int pos = 0;

    QStringList params;
    for(const auto &r : data)
        params.append(QString("('%1', %2)").arg(r).arg(++pos));

    return params.join(",");
}

QStringList TableCreator::rangs()
{
    QStringList r = {"рядовой", "ефрейтор",
                     "младший сержант", "сержант", "старший сержант", "старшина",
                     "прапорщик", "старший прапорщик",
                     "младший лейтенант", "лейтенант", "старший лейтенант", "капитан",
                     "майор", "подполковник", "полковник",
                     "генерал-майор", "генерал-лейтенант", "генерал-полковник", "генерал армии",
                     "Маршал РФ"};

    return r;
}

QStringList TableCreator::ageGroups()
{
    QStringList ag = {"1", "2", "3", "4", "5"};

    return ag;
}

QStringList TableCreator::groups()
{
    QStringList g = {"Контрольная", "Тестовая"};

    return g;
}

QStringList TableCreator::subGroups()
{
    QStringList sg = {"Верхние конечности", "Нижние конечности"};

    return sg;
}

QStringList TableCreator::clearance()
{
    QStringList c = {"Допущен"};

    return c;
}

QStringList TableCreator::diagnosis()
{
    QStringList d = {"Диагноз"};

    return d;
}

void TableCreator::createExaminee(QSqlDatabase *db, const QStringList &tables)
{
    QString name = "examinees";
    QStringList params = {
        "id INTEGER PRIMARY KEY AUTOINCREMENT",
        "age_group INTEGER",
        "test_group INTEGER",
        "subgroup INTEGER",
        "rang INTEGER",
        "department INTEGER",
        "surname VARCHAR(255)",
        "name VARCHAR(255)",
        "middle_name VARCHAR(255)",
        "born DATE",
        "clearance INTEGER",
        "diagnos INTEGER",
        "diseases TEXT",
        "comments TEXT"
    };

    createTable(name, params, db, tables);
}

//void TableCreator::createDepartments(QSqlDatabase *db, const QStringList &tables)
//{
//    QString name = "departments";
//    QStringList params = {
//        "id INTEGER PRIMARY KEY AUTOINCREMENT",
//        "name VARCHAR(255)",
//        "parent INTEGER"
//    };

//    createTable(name, params, db, tables);
//}

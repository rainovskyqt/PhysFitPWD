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
    createDictionary("diagnosis", db, tables);
    createDictionary("departments", db, tables);
    createDictionary("subdivision", db, tables);
    createDictionary("exercise_direction", db, tables);
    createDictionary("exercise_units", db, tables);

    createExaminee(db, tables);
    createTest(db, tables);
    createExercise(db, tables);
    createTestExercise(db, tables);
    // createExerciseGrade(db, tables);

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
    queryStrings.append(QString("INSERT INTO rangs(name, orderPlace) VALUES %2")
                        .arg(dictionaryParams(rangs())));
    queryStrings.append(QString("INSERT INTO age_groups(name, orderPlace) VALUES %2")
                        .arg(dictionaryParams(ageGroups())));
    queryStrings.append(QString("INSERT INTO groups(name, orderPlace) VALUES %2")
                        .arg(dictionaryParams(groups())));
    queryStrings.append(QString("INSERT INTO sub_groups(name, orderPlace) VALUES %2")
                        .arg(dictionaryParams(subGroups())));
    queryStrings.append(QString("INSERT INTO exercise_direction(name, orderPlace) VALUES %2")
                        .arg(dictionaryParams(exerciseDirection())));
     queryStrings.append(QString("INSERT INTO exercise_units(name, orderPlace) VALUES %2")
                         .arg(dictionaryParams(exerciseUnits())));

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

QStringList TableCreator::diagnosis()
{
    QStringList d = {"Диагноз"};

    return d;
}

QStringList TableCreator::exerciseDirection()
{
    QStringList d = {"Больше лучше", "Меньше лучше"};
    return d;
}

QStringList TableCreator::exerciseUnits()
{
    QStringList d = {"Секунды", "Минуты,Секунды", "Повторы", "Сантиметры", "Метры"};
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
        "subdivision INTEGER",
        "surname VARCHAR(255)",
        "name VARCHAR(255)",
        "middle_name VARCHAR(255)",
        "born DATE",
        "weight INTEGER",
        "clearance INTEGER",
        "diagnos INTEGER",
        "diseases TEXT",
        "comments TEXT"
    };

    createTable(name, params, db, tables);
}

void TableCreator::createTest(QSqlDatabase *db, const QStringList &tables)
{
    QString name = "tests";
    QStringList params = {
        "id INTEGER PRIMARY KEY AUTOINCREMENT",
        "name TEXT",
        "age_group INTEGER",
        "subgroup INTEGER"
    };

    createTable(name, params, db, tables);
}

void TableCreator::createExercise(QSqlDatabase *db, const QStringList &tables)
{
    QString name = "exercise";
    QStringList params = {
        "id INTEGER PRIMARY KEY AUTOINCREMENT",
        "name TEXT",
        "units INTEGER",
        "direction INTEGER"
    };

    createTable(name, params, db, tables);
}

void TableCreator::createTestExercise(QSqlDatabase *db, const QStringList &tables)
{
    QString name = "test_exercises";
    QStringList params = {
        "id INTEGER PRIMARY KEY AUTOINCREMENT",
        "test INTEGER",
        "exercise INTEGER",
        "grades INTEGER"
    };

    createTable(name, params, db, tables);
}

void TableCreator::createExerciseGrade(QSqlDatabase *db, const QStringList &tables)
{
    QString name = "exercises_grade";
    QStringList params = {
        "id INTEGER PRIMARY KEY AUTOINCREMENT",
        "exercise INTEGER",
        "grade INTEGER",
        "points INTEGER"
    };

    createTable(name, params, db, tables);
}

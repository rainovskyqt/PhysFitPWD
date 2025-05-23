#ifndef TABLECREATOR_H
#define TABLECREATOR_H

#include <QObject>

#include <QSqlDatabase>

class TableCreator : public QObject
{
    Q_OBJECT
public:

    explicit TableCreator(QObject *parent = nullptr);
    bool createTables(QSqlDatabase *db);
    bool addDefaultData(QSqlDatabase *db);

signals:

private:
    bool createTable(const QString& name,
                     const QStringList &params,
                     QSqlDatabase* db,
                     const QStringList& tables);

    bool createDictionary(const QString &name, QSqlDatabase *db, const QStringList &tables);
    void addDefaultDictionary(QSqlDatabase *db);
    QString dictionaryParams(const QStringList data);
    QStringList rangs();
    QStringList ageGroups();
    QStringList groups();
    QStringList subGroups();
    QStringList clearance();
    QStringList diagnosis();

//    void createDepartments(QSqlDatabase *db, const QStringList &tables);
    void createExaminee(QSqlDatabase *db, const QStringList &tables);
};

#endif // TABLECREATOR_H

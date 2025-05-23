#include "examineemanager.h"

#include "database/baseworker.h"
#include <QVariant>

#include "department.h"
#include "examinee.h"

ExamineeManager::ExamineeManager(QObject *parent) : QObject(parent)
{
}

QVector<Department*> ExamineeManager::getDepartments()
{
    QString queryString = QString("SELECT id, name "
                                  "FROM departments "
                                  "ORDER BY name");

    auto *q = BaseWorker::get()->select(queryString);
    QVector<Department*> deps;

    while (q->next()) {
        deps.append(new Department(q->value("id").toInt(), q->value("name").toString()));
    }

    delete q;

    return deps;
}

Examinee *ExamineeManager::getExaminee(int id)
{
    QString queryString = "SELECT id, age_group,test_group, subgroup, rang, department, "
                          "surname, name, middle_name, born, "
                          "clearance, diagnos, diseases, comments "
                          "FROM examinees "
                          "WHERE id = :id";

    QMap<QString, QVariant>params;
    params.insert(":id", QVariant(id));

    auto *q = BaseWorker::get()->select(queryString, params);
    auto e = new Examinee();

    q->next();
    e->setId(q->value("id").toInt());
    e->setAgeGroup(q->value("age_group").toInt());
    e->setTestGroup(q->value("test_group").toInt());
    e->setSubGroup(q->value("subgroup").toInt());
    e->setRang(q->value("rang").toInt());
    e->setDepartment(q->value("department").toInt());
    e->setSurname(q->value("surname").toString());
    e->setName(q->value("name").toString());
    e->setMiddleName(q->value("middle_name").toString());
    e->setBorn(q->value("born").toDate());
    e->setClearance(q->value("clearance").toInt());
    e->setDiagnos(q->value("diagnos").toInt());
    e->setDiseases(q->value("diseases").toString());
    e->setComments(q->value("comments").toString());

    return e;
}

void ExamineeManager::saveExaminee(Examinee *e)
{
    QString insert = QString("INSERT INTO examinees (age_group, test_group, subgroup, rang, department, "
                             "surname, name, middle_name, born, clearance, diagnos, diseases, comments) "
                             "VALUES (:age_group, :test_group, :subgroup, :rang, :department, "
                             ":surname, :name, :middle_name, :born, :clearance, :diagnos, :diseases, :comments)");
    QString update = QString("UPDATE examinees SET age_group = :age_group, test_group = :test_group, subgroup = :subgroup, "
                             "rang = :rang, department = :department, surname = :surname, name = :name, "
                             "middle_name = :middle_name, born = :born, clearance = :clearance, diagnos = :diagnos, "
                             "diseases = :diseases, comments = :comments"
                             );

    QMap<QString, QVariant>params;
    params.insert(":id", QVariant(e->id()));
    params.insert(":age_group", QVariant(e->ageGroup()));
    params.insert(":test_group", QVariant(e->testGroup()));
    params.insert(":subgroup", QVariant(e->subGroup()));
    params.insert(":rang", QVariant(e->rang()));
    params.insert(":department", QVariant(e->department()));
    params.insert(":surname", QVariant(e->surname()));
    params.insert(":name", QVariant(e->name()));
    params.insert(":middle_name", QVariant(e->middleName()));
    params.insert(":born", QVariant(e->born()));
    params.insert(":clearance", QVariant(e->clearance()));
    params.insert(":diagnos", QVariant(e->diagnos()));
    params.insert(":diseases", QVariant(e->diseases()));
    params.insert(":comments", QVariant(e->comments()));

    if(e->id()){
        BaseWorker::get()->updateOrDelete(update, params);
    } else {
        int id = BaseWorker::get()->insert(insert, params);
        e->setId(id);
    }
}

QMultiHash<QString, QPair<QString, int> > ExamineeManager::examineeList(int dep)
{
    QString depStr = "";
     QMap<QString, QVariant>params;

    if(dep){
        depStr = "WHERE E.department = :department";
        params.insert(":department_id", dep);
    }

    QString queryString = QString("SELECT D.`name` AS d_name, E.id AS e_id, E.surname AS e_sname, E.`name` AS e_name, "
                                  "E.middle_name AS e_mname "
                                  "FROM departments D "
                                  "INNER JOIN examinees E ON E.department = D.id "
                                  "%1 "
                                  "ORDER BY d_name, e_sname").arg(depStr);

    QMultiHash<QString, QPair<QString, int> > exam;

    auto query = BaseWorker::get()->select(queryString, params);
    while (query->next()) {
        exam.insert(query->value("d_name").toString(),
                     qMakePair(QString("%1 %2 %3").arg(query->value("e_sname").toString(),
                                                       query->value("e_name").toString(),
                                                       query->value("e_mname").toString()),
                               query->value("e_id").toInt()));
    }
    return exam;
}

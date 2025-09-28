#include "examinee.h"

Examinee::Examinee(QObject *parent) : QObject(parent)
{
    m_id = 0;
    m_ageGroup = 0;
    m_testGroup = 0;
    m_subGroup = 0;
    m_rang = 0;
    m_department = 0;
    m_subdivision = 0;
    m_surname = "";
    m_name = "";
    m_middleName = "";
    m_born = QDate();
    m_weight = 0;
    m_diagnos = 0;
    m_diseases = "";
    m_comments = "";
}

int Examinee::id() const
{
    return m_id;
}

void Examinee::setId(int newId)
{
    m_id = newId;
}

int Examinee::ageGroup() const
{
    return m_ageGroup;
}

void Examinee::setAgeGroup(int newAgeGroup)
{
    m_ageGroup = newAgeGroup;
}

int Examinee::testGroup() const
{
    return m_testGroup;
}

void Examinee::setTestGroup(int newTestGroup)
{
    m_testGroup = newTestGroup;
}

int Examinee::subGroup() const
{
    return m_subGroup;
}

void Examinee::setSubGroup(int newSubGroup)
{
    m_subGroup = newSubGroup;
}

int Examinee::rang() const
{
    return m_rang;
}

void Examinee::setRang(int newRang)
{
    m_rang = newRang;
}

int Examinee::department() const
{
    return m_department;
}

void Examinee::setDepartment(int newDepartment)
{
    m_department = newDepartment;
}

const QString &Examinee::surname() const
{
    return m_surname;
}

void Examinee::setSurname(const QString &newSurname)
{
    m_surname = newSurname;
}

const QString &Examinee::name() const
{
    return m_name;
}

void Examinee::setName(const QString &newName)
{
    m_name = newName;
}

const QString &Examinee::middleName() const
{
    return m_middleName;
}

void Examinee::setMiddleName(const QString &newMiddleName)
{
    m_middleName = newMiddleName;
}

const QDate &Examinee::born() const
{
    return m_born;
}

void Examinee::setBorn(const QDate &newBorn)
{
    m_born = newBorn;
}

int Examinee::diagnos() const
{
    return m_diagnos;
}

void Examinee::setDiagnos(int newDiagnos)
{
    m_diagnos = newDiagnos;
}

const QString &Examinee::diseases() const
{
    return m_diseases;
}

void Examinee::setDiseases(const QString &newDiseases)
{
    m_diseases = newDiseases;
}

const QString &Examinee::comments() const
{
    return m_comments;
}

void Examinee::setComments(const QString &newComments)
{
    m_comments = newComments;
}

int Examinee::weight() const
{
    return m_weight;
}

void Examinee::setWeight(int newWeight)
{
    m_weight = newWeight;
}

int Examinee::subdivision() const
{
    return m_subdivision;
}

void Examinee::setSubdivision(int newSubdivision)
{
    m_subdivision = newSubdivision;
}

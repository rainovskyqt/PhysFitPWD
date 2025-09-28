#ifndef EXAMINEE_H
#define EXAMINEE_H

#include <QDate>
#include <QObject>

class Examinee : public QObject
{
    Q_OBJECT
public:
    explicit Examinee(QObject *parent = nullptr);

    int id() const;
    void setId(int newId);
    int ageGroup() const;
    void setAgeGroup(int newAgeGroup);
    int testGroup() const;
    void setTestGroup(int newTestGroup);
    int subGroup() const;
    void setSubGroup(int newSubGroup);
    int rang() const;
    void setRang(int newRang);
    int department() const;
    void setDepartment(int newDepartment);
    const QString &surname() const;
    void setSurname(const QString &newSurname);
    const QString &name() const;
    void setName(const QString &newName);
    const QString &middleName() const;
    void setMiddleName(const QString &newMiddleName);
    const QDate &born() const;
    void setBorn(const QDate &newBorn);
    int clearance() const;
    void setClearance(int newClearance);
    int diagnos() const;
    void setDiagnos(int newDiagnos);
    const QString &diseases() const;
    void setDiseases(const QString &newDiseases);
    const QString &comments() const;
    void setComments(const QString &newComments);

    int weight() const;
    void setWeight(int newWeight);

    int subdivision() const;
    void setSubdivision(int newSubdivision);

signals:

private:
    int m_id;
    int m_ageGroup;
    int m_testGroup;
    int m_subGroup;
    int m_rang;
    int m_department;
    int m_subdivision;
    QString m_surname;
    QString m_name;
    QString m_middleName;
    QDate m_born;
    int m_weight;
    int m_diagnos;
    QString m_diseases;
    QString m_comments;
};

#endif // EXAMINEE_H

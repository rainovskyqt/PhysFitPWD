#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QVector>
#include <QObject>

class Dictionary : public QObject
{
    Q_OBJECT
public:

    enum class Type{
        Rangs,
        AgeGroups,
        Groups,
        SubGroups,
        Diagnosis,
        Departments,
        Subdivision,
        ExerciseUnits,
        ExerciseDirection
    };


    explicit Dictionary(QObject *parent = nullptr);

    const QVector<QPair<int, QString>> values() const;
    void addVal(int id, QString name);

signals:

private:
    QVector<QPair<int, QString>> m_dict;
};

#endif // DICTIONARY_H

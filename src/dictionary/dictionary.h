#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QMap>
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
        Clearance,
        Diagnosis
    };

    explicit Dictionary(QObject *parent = nullptr);

    const QMap<int, QString> values() const;
    void addVal(int id, QString name);

signals:

private:
    QMap<int, QString> m_dict;
};

#endif // DICTIONARY_H

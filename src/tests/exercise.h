#ifndef EXERCISE_H
#define EXERCISE_H

#include <QObject>

class Exercise : public QObject
{
    Q_OBJECT
public:
    explicit Exercise(QObject *parent = nullptr);

    int id() const;
    void setId(int newId);
    QString name() const;
    void setName(const QString &newName);
    int units() const;
    void setUnits(int newUnits);
    int direction() const;
    void setDirection(int newDirection);

signals:

private:
    int m_id;
    QString m_name;
    int m_units;
    int m_direction;
};

#endif // EXERCISE_H

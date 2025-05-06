#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <QObject>

class Department : public QObject
{
    Q_OBJECT
public:
    explicit Department(int id, const QString &name, QObject *parent = nullptr);

    int id() const;
    const QString &name() const;

signals:

private:
    const int m_id;
    const QString m_name;

};

#endif // DEPARTMENT_H

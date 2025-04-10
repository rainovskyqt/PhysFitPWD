#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QString userName, QObject *parent = nullptr);

    QString userName() const;

signals:

private:
    const QString m_userName;
};

#endif // USER_H

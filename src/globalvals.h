#ifndef GLOBALVALS_H
#define GLOBALVALS_H

#include <QObject>
#include "user/user.h"

class GlobalVals : public QObject
{
    Q_OBJECT
public:
    explicit GlobalVals(QObject *parent = nullptr);

    static GlobalVals *get();

    const User *user() const;
    void setUser(User *user);

signals:

private:
    User *m_user;
};

#endif // GLOBALVALS_H

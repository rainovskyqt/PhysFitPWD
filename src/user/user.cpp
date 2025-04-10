#include "user.h"

User::User(QString userName, QObject *parent) : QObject(parent)
    , m_userName(userName)
{

}

QString User::userName() const
{
    return m_userName;
}

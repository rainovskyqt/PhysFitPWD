#include "globalvals.h"

Q_GLOBAL_STATIC(GlobalVals, staticInst)

GlobalVals::GlobalVals(QObject *parent)
    : QObject{parent}
    , m_user(new User("NoName"))
{}

GlobalVals *GlobalVals::get()
{
    return staticInst;
}

const User *GlobalVals::user() const
{
    return m_user;
}

void GlobalVals::setUser(User *user)
{
    if(m_user != nullptr)
        m_user->deleteLater();

    m_user = user;
    m_user->setParent(this);
}

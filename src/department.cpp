#include "department.h"

Department::Department(int id, const QString &name, QObject *parent) : QObject(parent)
  , m_id(id)
  , m_name(name)
{}

int Department::id() const
{
    return m_id;
}

const QString &Department::name() const
{
    return m_name;
}

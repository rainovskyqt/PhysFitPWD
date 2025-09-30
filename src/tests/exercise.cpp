#include "exercise.h"

Exercise::Exercise(QObject *parent)
    : QObject{parent}
    , m_name{""}
    , m_units{0}
    , m_direction{0}
{}

int Exercise::id() const
{
    return m_id;
}

void Exercise::setId(int newId)
{
    m_id = newId;
}

QString Exercise::name() const
{
    return m_name;
}

void Exercise::setName(const QString &newName)
{
    m_name = newName;
}

int Exercise::units() const
{
    return m_units;
}

void Exercise::setUnits(int newUnits)
{
    m_units = newUnits;
}

int Exercise::direction() const
{
    return m_direction;
}

void Exercise::setDirection(int newDirection)
{
    m_direction = newDirection;
}

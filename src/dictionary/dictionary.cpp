#include "dictionary.h"

Dictionary::Dictionary(QObject *parent)
    : QObject{parent}
{}

const QMap<int, QString> Dictionary::values() const
{
    return m_dict;
}

void Dictionary::addVal(int id, QString name)
{
    m_dict.insert(id, name);
}

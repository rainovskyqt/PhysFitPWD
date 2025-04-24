#include "dictionary.h"

Dictionary::Dictionary(QObject *parent)
    : QObject{parent}
{}

const QVector<QPair<int, QString>> Dictionary::values() const
{
    return m_dict;
}

void Dictionary::addVal(int id, QString name)
{
    m_dict.append(qMakePair(id, name));
}

#include "dictionary.h"

Dictionary::Dictionary(QObject *parent)
    : QObject{parent}
{
}

const QVector<QPair<int, QString>> Dictionary::values() const
{
    return m_dict;
}

void Dictionary::addVal(int id, QString name)
{
    m_dict.append(qMakePair(id, name));
}

QString Dictionary::value(int id)
{
    for(const auto &v : qAsConst(m_dict))
        if(v.first == id)
            return v.second;

    return QString();
}

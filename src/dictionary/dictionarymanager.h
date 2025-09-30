#ifndef DICTIONARYMANAGER_H
#define DICTIONARYMANAGER_H

#include "dictionary.h"

#include <QComboBox>
#include <QMap>
#include <QObject>

using DType = Dictionary::Type;

class DictionaryManager : public QObject
{
    Q_OBJECT
public:
    explicit DictionaryManager(QObject *parent = nullptr);

    Dictionary *getDictionary(DType type);
    void addDictory(DType type, QString name);
    void editDictory(DType type, int id, QString name, int orderPlace);
    void deleteDictory(DType type, int id);
    void swapPlace(DType type, int idFirst, int idSecond);
    QString humanName(DType type);
    void loadDictionary(DType type, QComboBox *box);


signals:

private:
    QString getDictonaryTable(DType type);
    void updateOrderPlace(DType type, int id);
    int getOrderPlace(DType type, int id);

    QMap<DType, QString> m_humanName;
};

#endif // DICTIONARYMANAGER_H

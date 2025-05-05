#ifndef DICTIONARYMANAGER_H
#define DICTIONARYMANAGER_H

#include "dictionary.h"

#include <QObject>

class DictionaryManager : public QObject
{
    Q_OBJECT
public:
    explicit DictionaryManager(QObject *parent = nullptr);

    Dictionary *getDictionary(Dictionary::Type type);
    void addDictory(Dictionary::Type type, QString name);
    void editDictory(Dictionary::Type type, int id, QString name, int orderPlace);
    void deleteDictory(Dictionary::Type type, int id);
    void swapPlace(Dictionary::Type type, int idFirst, int idSecond);

signals:

private:
    QString getDictonaryTable(Dictionary::Type type);
    void updateOrderPlace(Dictionary::Type type, int id);
    int getOrderPlace(Dictionary::Type type, int id);
};

#endif // DICTIONARYMANAGER_H

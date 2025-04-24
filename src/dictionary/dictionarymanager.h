#ifndef DICTIONARYMANAGER_H
#define DICTIONARYMANAGER_H

#include "dictionary.h"

#include <QObject>

class DictionaryManager : public QObject
{
    Q_OBJECT
public:
    explicit DictionaryManager(QObject *parent = nullptr);

    static Dictionary *getDictionary(Dictionary::Type type);
    static void addDictory(Dictionary::Type type, QString name);
    static void editDictory(Dictionary::Type type, int id, QString name, int orderPlace);
    static void deleteDictory(Dictionary::Type type, int id);
    static void swapPlace(Dictionary::Type type, int idFirst, int idSecond);

signals:

private:
    static QString getDictonaryTable(Dictionary::Type type);
    static void updateOrderPlace(Dictionary::Type type, int id);
    static int getOrderPlace(Dictionary::Type type, int id);
};

#endif // DICTIONARYMANAGER_H

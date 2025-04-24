#ifndef BASEWORKER_H
#define BASEWORKER_H

#include <QObject>
#include <QSqlQuery>

#include <dictionary/dictionary.h>

class DataBase;

class BaseWorker : public QObject
{
    Q_OBJECT
public:
    explicit BaseWorker(QObject *parent = nullptr);
    void init(QString baseName);
    static BaseWorker *get();

    Dictionary *getDictionary(Dictionary::Type type);
    void addDictory(Dictionary::Type type, QString name);
    void editDictory(Dictionary::Type type, int id, QString name, int orderPlace);
    void deleteDictory(Dictionary::Type type, int id);

signals:

private:
    QSqlDatabase m_base;

    bool checkBasefile(const QString &fileName);

    QSqlQuery *select(QString queryText, QMap<QString, QVariant> params = {});
    int insert(QString queryText, QMap<QString, QVariant> params);
    void updateOrDelete(QString queryText, QMap<QString, QVariant> params);
    int lastInsertId();

    QSqlQuery *executeQuery(const QString& queryText,
                            const QMap<QString, QVariant>& params = {});

    QString getDictonaryTable(Dictionary::Type type);
    void updateOrderPlace(Dictionary::Type type, int id);
};

#endif // BASEWORKER_H

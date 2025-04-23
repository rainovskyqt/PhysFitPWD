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
};

#endif // BASEWORKER_H

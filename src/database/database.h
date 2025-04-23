#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlError>

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(const QString &connectionName, QObject *parent = nullptr);
    ~DataBase();
    static DataBase* make(const QString &baseName, const QString &connectionName = "main");
    QSqlError lastError() const;

signals:

private:
    QString m_connectionName;
    QSqlError m_lastError;

    static bool checkBasefile(const QString &fileName);

};

#endif // DATABASE_H

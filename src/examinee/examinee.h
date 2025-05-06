#ifndef EXAMINEE_H
#define EXAMINEE_H

#include <QObject>

class Examinee : public QObject
{
    Q_OBJECT
public:
    explicit Examinee(QObject *parent = nullptr);

signals:

};

#endif // EXAMINEE_H

#ifndef MISC_H
#define MISC_H

#include <QComboBox>
#include <QObject>

class Misc : public QObject
{
    Q_OBJECT
public:
    Misc();

    static void setBoxValue(int val, QComboBox *box);
};

#endif // MISC_H

#ifndef TESTSLIST_H
#define TESTSLIST_H

#include <QWidget>
#include "dictionary/dictionarywidget.h"

class TestsList : public DictionaryWidget
{
    Q_OBJECT
public:
    explicit TestsList(QWidget *parent = nullptr);

signals:

private:

};

#endif // TESTSLIST_H

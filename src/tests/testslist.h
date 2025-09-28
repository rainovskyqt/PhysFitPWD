#ifndef TESTSLIST_H
#define TESTSLIST_H

#include <QWidget>

namespace Ui {
class TestsList;
}

class TestsList : public QWidget
{
    Q_OBJECT

public:
    explicit TestsList(QWidget *parent = nullptr);
    ~TestsList();

private slots:


    void on_btn_add_clicked();

private:
    Ui::TestsList *ui;

    void selectTests();
};

#endif // TESTSLIST_H

#ifndef TESTEXESISE_H
#define TESTEXESISE_H

#include <QDialog>

namespace Ui {
class TestExesise;
}

class TestExesise : public QDialog
{
    Q_OBJECT

public:
    explicit TestExesise(QWidget *parent = nullptr, int exesiseId = 0);
    ~TestExesise();

private slots:
    void on_cb_max_currentIndexChanged(int index);
    void on_cb_min_currentIndexChanged(int index);

private:
    Ui::TestExesise *ui;
};

#endif // TESTEXESISE_H

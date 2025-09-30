#ifndef TESTFORM_H
#define TESTFORM_H

#include <QDialog>

namespace Ui {
class TestForm;
}

class TestForm : public QDialog
{
    Q_OBJECT

public:
    explicit TestForm(QWidget *parent = nullptr, int testId = 0);
    ~TestForm();

private slots:
    void on_btn_add_clicked();

private:
    Ui::TestForm *ui;

    void loadDictionaries();
};

#endif // TESTFORM_H

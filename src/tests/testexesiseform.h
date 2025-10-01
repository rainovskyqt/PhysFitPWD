#ifndef TESTEXESISEFORM_H
#define TESTEXESISEFORM_H

#include <QDialog>
#include "testexercise.h"

namespace Ui {
class TestExesiseForm;
}

class TestExesiseForm : public QDialog
{
    Q_OBJECT

public:
    explicit TestExesiseForm(QWidget *parent = nullptr);
    ~TestExesiseForm();

    TestExercise *exercise();
    void setTestExercise(TestExercise *e);

private slots:
    void on_btn_add_clicked();
    void on_btn_delete_clicked();
    void on_btn_cancel_clicked();
    void on_btn_ok_clicked();

private:
    Ui::TestExesiseForm *ui;

    int m_id;
    void loadExercises();
    QString joinGrades();
    void parceGrades(QString g);
    bool checkExercises();
};

#endif // TESTEXESISEFORM_H

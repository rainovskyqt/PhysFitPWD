#ifndef TESTFORM_H
#define TESTFORM_H

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class TestForm;
}

class Test;

class TestForm : public QDialog
{
    Q_OBJECT

public:
    explicit TestForm(QWidget *parent = nullptr, int testId = 0);
    ~TestForm();
    void load(int id);

private slots:
    void on_btn_add_clicked();
    void on_btn_delete_clicked();
    void on_btn_edit_clicked();

    void on_lw_exercises_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::TestForm *ui;

    int m_id;
    QList<int> m_deleted;

    void loadDictionaries();
    void save();
    void setExercises(Test *t);
    void appendTestExecises(Test *t);
};

#endif // TESTFORM_H

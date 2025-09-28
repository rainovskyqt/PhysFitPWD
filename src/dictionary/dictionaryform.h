#ifndef DICTIONARYFORM_H
#define DICTIONARYFORM_H

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class DictionaryForm;
}

class DictionaryForm : public QDialog
{
    Q_OBJECT

public:
    explicit DictionaryForm(QWidget *parent = nullptr);
    ~DictionaryForm();

private slots:
    void on_btn_department_clicked();
    void on_btn_subdivision_clicked();
    void on_btn_rang_clicked();
    void on_btn_ageGroups_clicked();
    void on_btn_groups_clicked();
    void on_btn_subGroups_clicked();
    void on_btn_diagnosis_clicked();

private:
    Ui::DictionaryForm *ui;
};

#endif // DICTIONARYFORM_H

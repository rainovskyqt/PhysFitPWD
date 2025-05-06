#ifndef DICTIONARYFORM_H
#define DICTIONARYFORM_H

#include <QDialog>
#include <QListWidgetItem>
#include "dictionary/dictionary.h"

namespace Ui {
class DictionaryForm;
}

using T = Dictionary::Type;

class DictionaryForm : public QDialog
{
    Q_OBJECT

public:
    explicit DictionaryForm(QWidget *parent = nullptr);
    ~DictionaryForm();

private slots:
    void on_btn_department_clicked();
    void on_btn_rang_clicked();
    void on_btn_ageGroups_clicked();
    void on_btn_groups_clicked();
    void on_btn_subGroups_clicked();
    void on_btn_diagnosis_clicked();
    void on_btn_clearance_clicked();
    void on_btn_up_clicked();
    void on_btn_down_clicked();
    void on_btn_add_clicked();
    void on_btn_edit_clicked();
    void on_btn_delete_clicked();
    void on_lw_valuesList_itemDoubleClicked(QListWidgetItem *item);


private:
    Ui::DictionaryForm *ui;

    T m_currentDictory;

    void setDictionary(T type);
    bool exists(QString name);
    void swapOrder(int row1, int row2, int current);
};

#endif // DICTIONARYFORM_H

#ifndef DICTIONARYFORM_H
#define DICTIONARYFORM_H

#include <QDialog>
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
    void on_btn_rang_clicked();
    void on_btn_ageGroups_clicked();
    void on_btn_groups_clicked();
    void on_btn_subGroups_clicked();
    void on_btn_diagnosis_clicked();

    void on_btn_clearance_clicked();

private:
    Ui::DictionaryForm *ui;

    void setDictionary(T type);
};

#endif // DICTIONARYFORM_H

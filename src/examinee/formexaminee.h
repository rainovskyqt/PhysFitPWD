#ifndef FORMEXAMINEE_H
#define FORMEXAMINEE_H

#include <QWidget>
#include <QComboBox>

#include "dictionary/dictionary.h"

#include "examinee.h"

using DType = Dictionary::Type;
class Examinee;

namespace Ui {
class FormExaminee;
}

class FormExaminee : public QWidget
{
    Q_OBJECT

public:
    explicit FormExaminee(QWidget *parent = nullptr);
    ~FormExaminee();

public slots:
    QPair<QString, int> save();
    void reset();
    void loadForm(int baseId);
    void setDepartment(QString dep);

private:
    Ui::FormExaminee *ui;

    Examinee *m_examinee;

    void resetForm();
    void clearFields();
    void clearComboboxes();
    void clearLines();

    void loadDictionaries();
    void setFrom(Examinee *e);
    bool checkDate(QLineEdit *bl);
};

#endif // FORMEXAMINEE_H

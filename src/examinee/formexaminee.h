#ifndef FORMEXAMINEE_H
#define FORMEXAMINEE_H

#include <QWidget>
#include <QComboBox>

#include "dictionary/dictionary.h"

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
    void save();
    void reset();
    void loadForm(int baseId);

private:
    Ui::FormExaminee *ui;

    int m_baseId;

    void resetForm();
    void clearFields();
    void clearComboboxes();
    void clearLines();

    void loadDictionaries();
    void loadDictionary(DType type, QComboBox *box);
    void setFrom(Examinee *e);
    void setBoxValue(int val, QComboBox *box);
    bool checkDate(QLineEdit *bl);
};

#endif // FORMEXAMINEE_H

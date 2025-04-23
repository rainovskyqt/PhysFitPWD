#ifndef DICTIONARYFORM_H
#define DICTIONARYFORM_H

#include <QDialog>

namespace Ui {
class DictionaryForm;
}

class DictionaryForm : public QDialog
{
    Q_OBJECT

public:
    explicit DictionaryForm(QWidget *parent = nullptr);
    ~DictionaryForm();

private:
    Ui::DictionaryForm *ui;
};

#endif // DICTIONARYFORM_H

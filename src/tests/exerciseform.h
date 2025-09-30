#ifndef EXERCISEFORM_H
#define EXERCISEFORM_H

#include <QDialog>

class Exercise;

namespace Ui {
class ExerciseForm;
}

class ExerciseForm : public QDialog
{
    Q_OBJECT

public:
    explicit ExerciseForm(QWidget *parent = nullptr);
    ~ExerciseForm();
    void load(int id);

private:
    Ui::ExerciseForm *ui;

    int m_id;

    void loadDictionaries();
    void save();
};

#endif // EXERCISEFORM_H

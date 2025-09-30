#ifndef EXERCISELIST_H
#define EXERCISELIST_H

#include <QListWidgetItem>
#include <QWidget>

class Exercise;

namespace Ui {
class ExerciseList;
}

class ExerciseList : public QWidget
{
    Q_OBJECT

public:
    explicit ExerciseList(QWidget *parent = nullptr);
    ~ExerciseList();

private slots:
    void on_btn_add_clicked();
    void on_btn_edit_clicked();

    void on_btn_delete_clicked();

    void on_lw_exerciseList_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::ExerciseList *ui;
    int getId();
    void loadExercises();
};

#endif // EXERCISELIST_H

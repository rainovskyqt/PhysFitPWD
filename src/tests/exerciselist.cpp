#include "exerciselist.h"
#include "ui_exerciselist.h"

#include "exercise.h"
#include "exerciseform.h"
#include "testsmanager.h"

#include <QMessageBox>

ExerciseList::ExerciseList(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ExerciseList)
{
    ui->setupUi(this);
    loadExercises();
}

ExerciseList::~ExerciseList()
{
    delete ui;
}

void ExerciseList::on_btn_add_clicked()
{
    auto ef = new ExerciseForm(this);
    if(ef->exec() == QDialog::Accepted)
        loadExercises();
    ef->deleteLater();
}

int ExerciseList::getId()
{
    auto item = ui->lw_exerciseList->currentItem();
    if(item == nullptr){
        QMessageBox::information(this, "Не выбрано", "Не выбрано упражнение");
        return -1;
    }

    auto id = item->data(Qt::UserRole).toInt();
    return id;
}

void ExerciseList::loadExercises()
{
    ui->lw_exerciseList->clear();
    auto tm = new TestsManager(this);
    auto l = tm->loadExercises();

    for(const auto e : qAsConst(l)){
        auto item = new QListWidgetItem(ui->lw_exerciseList);
        item->setText(e->name());
        item->setData(Qt::UserRole, e->id());
        ui->lw_exerciseList->addItem(item);
    }

    qDeleteAll(l);
}


void ExerciseList::on_btn_edit_clicked()
{
    auto id = getId();
    if(id == -1)
        return;

    auto ef = new ExerciseForm(this);
    ef->load(id);
    if(ef->exec() == QDialog::Accepted)
        loadExercises();
    ef->deleteLater();
}


void ExerciseList::on_btn_delete_clicked()
{
    auto id = getId();
    if(id == -1)
        return;

    int answer = QMessageBox::question(this, "Удаление упражнения", "Удалить упражнение?");
    if(answer == QMessageBox::No)
        return;

    auto tm = new TestsManager(this);
    tm->deleteExercise(id);
    loadExercises();
}


void ExerciseList::on_lw_exerciseList_itemDoubleClicked(QListWidgetItem *item)
{
    Q_UNUSED(item)
    on_btn_edit_clicked();
}


#include "testexesiseform.h"
#include "ui_testexesiseform.h"

#include "tests/testsmanager.h"
#include "exercise.h"
#include "testexercise.h"
#include <QMessageBox>
#include <misc.h>

TestExesiseForm::TestExesiseForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TestExesiseForm)
    , m_id{0}
{
    ui->setupUi(this);
    loadExercises();
}

TestExesiseForm::~TestExesiseForm()
{
    delete ui;
}

TestExercise *TestExesiseForm::exercise()
{
    auto e = ui->cb_exercises->currentData().value<Exercise*>();
    auto te = new TestExercise();

    te->setExerciseId(e->id());
    te->setExerciseName(e->name());
    te->setGrades(joinGrades());

    return te;
}

void TestExesiseForm::setTestExercise(TestExercise *e)
{
    m_id = e->id();
    Misc::setBoxValue(e->exerciseId(), ui->cb_exercises);
    parceGrades(e->grades());
}

void TestExesiseForm::loadExercises()
{
    auto tm = new TestsManager(this);
    auto el = tm->loadExercises();

    for(const auto e : qAsConst(el)){
        ui->cb_exercises->addItem(e->name(), QVariant::fromValue(e));
    }

    checkExercises();
}

QString TestExesiseForm::joinGrades()
{
    QStringList grades;
    for(int i = 0; i < ui->tw_grades->rowCount(); ++i){
        grades.append(QString("%1,%2").arg(ui->tw_grades->item(i, 0)->text(), ui->tw_grades->item(i, 1)->text()));
    }
    return grades.join(";");
}

void TestExesiseForm::parceGrades(QString g)
{
   const auto grades = g.split(";");
    for(const auto &gr : grades){
        int row = ui->tw_grades->rowCount();
        ui->tw_grades->insertRow(row);

        auto points = gr.split(",");
        QTableWidgetItem *item = new QTableWidgetItem(points.at(0));
        ui->tw_grades->setItem(row, 0, item);
        item = new QTableWidgetItem(points.at(1));
        ui->tw_grades->setItem(row, 1, item);
    }
}

bool TestExesiseForm::checkExercises()
{
    if(ui->cb_exercises->count() == 0){
        QMessageBox::information(this, "Нет упражнений", "Не создано ни одного упражнения, данные не будут сохранены");
        return false;
    }

    return true;
}

void TestExesiseForm::on_btn_add_clicked()
{
    int row = ui->tw_grades->rowCount();
    ui->tw_grades->insertRow(row);
}

void TestExesiseForm::on_btn_delete_clicked()
{
    auto selected = ui->tw_grades->selectedItems();
    if(selected.isEmpty())
        return;
    int row = selected.at(0)->row();
    ui->tw_grades->removeRow(row);
}

void TestExesiseForm::on_btn_cancel_clicked()
{
    reject();
}

void TestExesiseForm::on_btn_ok_clicked()
{
    if(checkExercises())
       accept();
}


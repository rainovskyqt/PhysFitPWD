#include "testform.h"
#include "testsmanager.h"
#include "ui_testform.h"

#include "testexesiseform.h"
#include "dictionary/dictionary.h"

#include <dictionary/dictionarymanager.h>
#include "test.h"

#include <QMessageBox>
#include <misc.h>
#include "testexercise.h"

TestForm::TestForm(QWidget *parent, int testId) :
    QDialog(parent),
    ui(new Ui::TestForm)
{
    ui->setupUi(this);
    loadDictionaries();

    connect(this, &QDialog::accepted, this, &TestForm::save);
}

TestForm::~TestForm()
{
    delete ui;
}

void TestForm::load(int id)
{
    auto tm = new TestsManager(this);
    auto t = tm->test(id);

    ui->line_name->setText(t->name());
    Misc::setBoxValue(t->subgroup(), ui->cb_subgroup);
    Misc::setBoxValue(t->ageGroup(), ui->cb_ageGroup);
    m_id = id;
    setExercises(t);

    t->deleteLater();
}

void TestForm::on_btn_add_clicked()
{
    auto ef = new TestExesiseForm(this);
    if(ef->exec() == QDialog::Rejected)
        return;

    auto e = ef->exercise();
    auto item = new QListWidgetItem(e->exerciseName());
    item->setData(Qt::UserRole, QVariant::fromValue(e));
    ui->lw_exercises->addItem(item);
}

void TestForm::loadDictionaries()
{
    auto dm = new DictionaryManager(this);
    dm->loadDictionary(Dictionary::Type::SubGroups, ui->cb_subgroup);
    dm->loadDictionary(Dictionary::Type::AgeGroups, ui->cb_ageGroup);
    dm->deleteLater();
}

void TestForm::save()
{
    auto t = new Test(this);
    auto tm = new TestsManager(this);

    t->setId(m_id);
    t->setName(ui->line_name->text());
    t->setSubgroup(ui->cb_subgroup->currentData().toInt());
    t->setAgeGroup(ui->cb_ageGroup->currentData().toInt());
    t->setDeleted(m_deleted);
    appendTestExecises(t);

    tm->saveTest(t);

    t->deleteLater();
}

void TestForm::setExercises(Test *t)
{
    const auto el = t->exercises();

    for(const auto e : el){
        auto item = new QListWidgetItem(ui->lw_exercises);
        item->setText(e->exerciseName());
        item->setData(Qt::UserRole, QVariant::fromValue(e));
        ui->lw_exercises->addItem(item);
    }
}

void TestForm::appendTestExecises(Test *t)
{
    for(int i = 0; i < ui->lw_exercises->count(); ++i){
        auto te = ui->lw_exercises->item(i)->data(Qt::UserRole).value<TestExercise*>();
        t->addExercise(te);
    }
}

void TestForm::on_btn_delete_clicked()
{
    auto item = ui->lw_exercises->currentItem();
    if(!item)
        return;

    auto te = item->data(Qt::UserRole).value<TestExercise*>();

    int answer = QMessageBox::question(this, "Удаление упражнения", "Удалить упражнение?");
    if(answer == QMessageBox::No)
        return;
    if(te->id())
        m_deleted.append(te->id());
    delete ui->lw_exercises->takeItem(ui->lw_exercises->currentRow());
}


void TestForm::on_btn_edit_clicked()
{
    auto item = ui->lw_exercises->currentItem();
    if(!item)
        return;

    auto te = item->data(Qt::UserRole).value<TestExercise*>();
    auto ef = new TestExesiseForm(this);
    ef->setTestExercise(te);
    if(ef->exec() == QDialog::Accepted){
        delete te;
        te = ef->exercise();
        item->setData(Qt::UserRole, QVariant::fromValue(te));
        item->setText(te->exerciseName());
    }

    ef->deleteLater();
}


void TestForm::on_lw_exercises_itemDoubleClicked(QListWidgetItem *item)
{
    Q_UNUSED(item)
    on_btn_edit_clicked();
}


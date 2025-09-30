#include "exercise.h"
#include "exerciseform.h"
#include "testsmanager.h"
#include "ui_exerciseform.h"

#include <dictionary/dictionarymanager.h>

#include <misc.h>

ExerciseForm::ExerciseForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ExerciseForm)
    , m_id{0}
{
    ui->setupUi(this);

    loadDictionaries();

    connect(this, &QDialog::accepted, this, &ExerciseForm::save);
}

ExerciseForm::~ExerciseForm()
{
    delete ui;
}

void ExerciseForm::loadDictionaries()
{
    auto dm = new DictionaryManager(this);
    dm->loadDictionary(Dictionary::Type::ExerciseDirection, ui->cb_direction);
    dm->loadDictionary(Dictionary::Type::ExerciseUnits, ui->cb_unuts);
    dm->deleteLater();
}

void ExerciseForm::load(int id)
{
    auto tm = new TestsManager(this);
    auto e = tm->exercise(id);

    ui->line_name->setText(e->name());
    Misc::setBoxValue(e->units(), ui->cb_unuts);
    Misc::setBoxValue(e->direction(), ui->cb_direction);
    m_id = id;

    e->deleteLater();
}

void ExerciseForm::save()
{
    auto e = new Exercise(this);
    auto tm = new TestsManager(this);

    e->setId(m_id);
    e->setName(ui->line_name->text());
    e->setUnits(ui->cb_unuts->currentData().toInt());
    e->setDirection(ui->cb_direction->currentData().toInt());

    tm->saveExercise(e);

    e->deleteLater();
}

#include "testform.h"
#include "ui_testform.h"

#include "testexesise.h"
#include "dictionary/dictionary.h"

#include <dictionary/dictionarymanager.h>

TestForm::TestForm(QWidget *parent, int testId) :
    QDialog(parent),
    ui(new Ui::TestForm)
{
    ui->setupUi(this);
    loadDictionaries();
}

TestForm::~TestForm()
{
    delete ui;
}

void TestForm::on_btn_add_clicked()
{
    auto e = new TestExesise(this);
    e->exec();
}

void TestForm::loadDictionaries()
{
    auto dm = new DictionaryManager(this);
    dm->loadDictionary(Dictionary::Type::SubGroups, ui->cb_subgroup);
    dm->loadDictionary(Dictionary::Type::AgeGroups, ui->cb_ageGroup);
    dm->deleteLater();
}


#include "dictionaryform.h"
#include "ui_dictionaryform.h"

#include "database/baseworker.h"

DictionaryForm::DictionaryForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DictionaryForm)
{
    ui->setupUi(this);
}

DictionaryForm::~DictionaryForm()
{
    delete ui;
}

void DictionaryForm::setDictionary(T type)
{
    ui->listWidget->clear();
    auto dicts = BaseWorker::get()->getDictionary(type);
    auto vals = dicts->values();

    for(auto it = vals.begin(); it != vals.end(); ++it){
        auto item = new QListWidgetItem(it.value(), ui->listWidget);
        item->setData(Qt::UserRole, it.key());
        ui->listWidget->addItem(item);
    }

    delete dicts;
}

void DictionaryForm::on_btn_rang_clicked()
{
    setDictionary(T::Rangs);
}

void DictionaryForm::on_btn_ageGroups_clicked()
{
    setDictionary(T::AgeGroups);
}

void DictionaryForm::on_btn_groups_clicked()
{
    setDictionary(T::Groups);
}

void DictionaryForm::on_btn_subGroups_clicked()
{
    setDictionary(T::SubGroups);
}

void DictionaryForm::on_btn_diagnosis_clicked()
{
    setDictionary(T::Diagnosis);
}

void DictionaryForm::on_btn_clearance_clicked()
{
    setDictionary(T::Clearance);
}

#include "dictionaryform.h"
#include "ui_dictionaryform.h"

#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>

DictionaryForm::DictionaryForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DictionaryForm)
{
    ui->setupUi(this);
    on_btn_department_clicked();
}

DictionaryForm::~DictionaryForm()
{
    delete ui;
}

void DictionaryForm::on_btn_department_clicked()
{
    ui->w_list->setDictionary(T::Departments);
}

void DictionaryForm::on_btn_rang_clicked()
{
    ui->w_list->setDictionary(T::Rangs);
}

void DictionaryForm::on_btn_ageGroups_clicked()
{
    ui->w_list->setDictionary(T::AgeGroups);
}

void DictionaryForm::on_btn_groups_clicked()
{
    ui->w_list->setDictionary(T::Groups);
}

void DictionaryForm::on_btn_subGroups_clicked()
{
    ui->w_list->setDictionary(T::SubGroups);
}

void DictionaryForm::on_btn_diagnosis_clicked()
{
    ui->w_list->setDictionary(T::Diagnosis);
}

void DictionaryForm::on_btn_subdivision_clicked()
{
    ui->w_list->setDictionary(T::Subdivision);
}


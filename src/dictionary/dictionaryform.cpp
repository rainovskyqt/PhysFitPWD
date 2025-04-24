#include "dictionaryform.h"
#include "ui_dictionaryform.h"

#include "database/baseworker.h"

#include <QInputDialog>
#include <QMessageBox>

DictionaryForm::DictionaryForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DictionaryForm)
{
    ui->setupUi(this);
    on_btn_rang_clicked();
}

DictionaryForm::~DictionaryForm()
{
    delete ui;
}

void DictionaryForm::setDictionary(T type)
{
    ui->lw_valuesList->clear();
    auto dicts = BaseWorker::get()->getDictionary(type);
    auto vals = dicts->values();

    for(auto it = vals.begin(); it != vals.end(); ++it){
        auto item = new QListWidgetItem(it.value(), ui->lw_valuesList);
        item->setData(Qt::UserRole, it.key());
        ui->lw_valuesList->addItem(item);
    }

    m_currentDictory = type;

    delete dicts;
}

bool DictionaryForm::exists(QString name)
{
    for(int i = 0; i < ui->lw_valuesList->count(); ++i)
        if(ui->lw_valuesList->item(i)->text() == name)
            return true;

    return false;
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

void DictionaryForm::on_btn_up_clicked()
{

}

void DictionaryForm::on_btn_down_clicked()
{

}

void DictionaryForm::on_btn_add_clicked()
{
    auto name = QInputDialog::getText(this, "Новое значение", "Введите новое значение");
    if(name.isEmpty())
        return;

    if(exists(name)){
        QMessageBox::information(this, "Уже существует", QString("Значение \"%1\" уже есть в списке").arg(name));
        return;
    }

    BaseWorker::get()->addDictory(m_currentDictory, name);
    setDictionary(m_currentDictory);
}

void DictionaryForm::on_btn_edit_clicked()
{
    auto item = ui->lw_valuesList->currentItem();
    if(item == nullptr)
        return;

    auto orderPlace = ui->lw_valuesList->row(item) + 1;
    auto id = item->data(Qt::UserRole).toInt();

    auto name = QInputDialog::getText(this, "Новое значение", "Введите новое значение", QLineEdit::Normal, item->text());
    if(name.isEmpty())
        return;

    BaseWorker::get()->editDictory(m_currentDictory, id, name, orderPlace);
    setDictionary(m_currentDictory);
}

void DictionaryForm::on_btn_delete_clicked()
{
    auto item = ui->lw_valuesList->currentItem();
    if(item == nullptr)
        return;

    if(QMessageBox::question(this, "Удаление значения", QString("Удалить значение \"%1\"?").arg(item->text()))
        == QMessageBox::No)
        return;

    int id = item->data(Qt::UserRole).toInt();

    BaseWorker::get()->deleteDictory(m_currentDictory, id);
    setDictionary(m_currentDictory);
}

void DictionaryForm::on_lw_valuesList_itemDoubleClicked(QListWidgetItem *item)
{
    Q_UNUSED(item)
    on_btn_edit_clicked();
}


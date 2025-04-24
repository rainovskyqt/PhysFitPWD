#include "dictionaryform.h"
#include "ui_dictionaryform.h"

#include "dictionarymanager.h"

#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>

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
    auto dicts = DictionaryManager::getDictionary(type);
    auto vals = dicts->values();

    for(auto v : vals){
        auto item = new QListWidgetItem(v.second);
        item->setData(Qt::UserRole, v.first);
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

void DictionaryForm::swapOrder(int row1, int row2, int current)
{
    int firstId = ui->lw_valuesList->item(row1)->data(Qt::UserRole).toInt();
    int secondId = ui->lw_valuesList->item(row2)->data(Qt::UserRole).toInt();

    DictionaryManager::swapPlace(m_currentDictory, firstId, secondId);
    setDictionary(m_currentDictory);

    ui->lw_valuesList->setCurrentRow(current);
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
    int row = ui->lw_valuesList->currentRow();
    if(row ==0)
        return;
    swapOrder(row -1, row, row -1);
}

void DictionaryForm::on_btn_down_clicked()
{
    int row = ui->lw_valuesList->currentRow();
    if(row == ui->lw_valuesList->count())
        return;
    swapOrder(row, row + 1, row + 1);
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

    DictionaryManager::addDictory(m_currentDictory, name);
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

    DictionaryManager::editDictory(m_currentDictory, id, name, orderPlace);
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

    DictionaryManager::deleteDictory(m_currentDictory, id);
    setDictionary(m_currentDictory);
}

void DictionaryForm::on_lw_valuesList_itemDoubleClicked(QListWidgetItem *item)
{
    Q_UNUSED(item)
    on_btn_edit_clicked();
}


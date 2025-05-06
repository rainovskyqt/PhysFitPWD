#include "formexaminee.h"
#include "ui_formexaminee.h"

#include <dictionary/dictionarymanager.h>

FormExaminee::FormExaminee(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormExaminee)
{
    ui->setupUi(this);

    resetForm();
    loadDictionaries();
}

FormExaminee::~FormExaminee()
{
    delete ui;
}

void FormExaminee::save()
{

}

void FormExaminee::reset()
{
    if(m_baseId){
        loadForm(m_baseId);
    } else {
        resetForm();
    }
}

void FormExaminee::loadForm(int baseId)
{
    m_baseId = baseId;
}

void FormExaminee::resetForm()
{
    m_baseId = 0;
    clearFields();
}

void FormExaminee::clearFields()
{
    clearComboboxes();
    clearLines();
}

void FormExaminee::clearComboboxes()
{
    auto list = this->findChildren<QComboBox*>();
    for(auto const u : qAsConst(list)){
        u->clear();
        u->addItem("-");
    }
}

void FormExaminee::clearLines()
{
    auto list = this->findChildren<QLineEdit*>();
    for(auto const u : qAsConst(list)){
        u->setText("");
    }
}

void FormExaminee::loadDictionaries()
{
    loadDictionary(DType::AgeGroups, ui->cb_ageGroup);
    loadDictionary(DType::Groups, ui->cb_group);
    loadDictionary(DType::SubGroups, ui->cb_subGroup);
    loadDictionary(DType::Rangs, ui->cb_rang);
    loadDictionary(DType::Departments, ui->cb_department);
    loadDictionary(DType::Clearance, ui->cb_clearance);
    loadDictionary(DType::Diagnosis, ui->cb_diagnos);
}

void FormExaminee::loadDictionary(DType type, QComboBox *box)
{
    auto mng = new DictionaryManager(this);
    auto dict = mng->getDictionary(type);
    auto const vals = dict->values();

    for(auto const &v : vals){
        box->addItem(v.second, v.first);
    }
}

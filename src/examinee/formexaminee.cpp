#include "examineemanager.h"
#include "formexaminee.h"
#include "ui_formexaminee.h"

#include <dictionary/dictionarymanager.h>
#include "examinee.h"
#include <QMessageBox>

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
    if(!checkDate(ui->line_born))
        return;

    auto mng = new ExamineeManager(this);
    auto e = new Examinee();

    e->setId(m_baseId);
    e->setAgeGroup(ui->cb_ageGroup->currentData().toInt());
    e->setTestGroup(ui->cb_group->currentData().toInt());
    e->setSubGroup(ui->cb_subGroup->currentData().toInt());
    e->setRang(ui->cb_rang->currentData().toInt());
    e->setDepartment(ui->cb_department->currentData().toInt());
    e->setSurname(ui->line_surname->text());
    e->setName(ui->line_name->text());
    e->setMiddleName(ui->line_middleName->text());
    e->setBorn(QDate::fromString(ui->line_born->text(), "dd.MM.yyyy"));
    e->setClearance(ui->cb_clearance->currentData().toInt());
    e->setDiagnos(ui->cb_diagnos->currentData().toInt());
    e->setDiseases(ui->text_diseases->toPlainText());
    e->setComments(ui->text_comments->toPlainText());

    mng->saveExaminee(e);
    setFrom(e);
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

    auto mng = new ExamineeManager(this);
    auto e = mng->getExaminee(baseId);

    setFrom(e);
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

void FormExaminee::setFrom(Examinee *e)
{
    setBoxValue(e->ageGroup(), ui->cb_ageGroup);
    setBoxValue(e->testGroup(), ui->cb_group);
    setBoxValue(e->subGroup(), ui->cb_subGroup);
    setBoxValue(e->rang(), ui->cb_rang);
    setBoxValue(e->department(), ui->cb_department);
    setBoxValue(e->clearance(), ui->cb_clearance);
    setBoxValue(e->diagnos(), ui->cb_diagnos);

    ui->line_surname->setText(e->surname());
    ui->line_name->setText(e->name());
    ui->line_middleName->setText(e->middleName());
    ui->line_born->setText(e->born().toString("dd.MM.yyyy"));

    ui->text_diseases->setPlainText(e->diseases());
    ui->text_comments->setPlainText(e->comments());

    e->deleteLater();
}

void FormExaminee::setBoxValue(int val, QComboBox *box)
{
    int index = box->findData(val, Qt::UserRole);
    box->setCurrentIndex(index == -1 ? 0 : index);
}

bool FormExaminee::checkDate(QLineEdit *bl)
{
    if(!QDate::fromString(bl->text(), "dd.MM.yyyy").isValid()){
        QMessageBox::information(this, "Неверная дата", "Введена неверная дата рождения, введите в формате дд.мм.гггг");
        return false;
    }
    return true;
}

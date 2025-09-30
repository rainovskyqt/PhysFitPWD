#include "examineemanager.h"
#include "formexaminee.h"
#include "ui_formexaminee.h"

#include <dictionary/dictionarymanager.h>
#include "examinee.h"
#include <QMessageBox>
#include <misc.h>

FormExaminee::FormExaminee(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormExaminee)
    , m_examinee(nullptr)
{
    ui->setupUi(this);

    resetForm();
    loadDictionaries();
}

FormExaminee::~FormExaminee()
{
    delete ui;
}

QPair<QString,int> FormExaminee::save()
{
    if(!checkDate(ui->line_born))
        return qMakePair(QString(), 0);

    auto mng = new ExamineeManager(this);
    if(m_examinee == nullptr)
        m_examinee = new Examinee();

    m_examinee->setAgeGroup(ui->cb_ageGroup->currentData().toInt());
    m_examinee->setTestGroup(ui->cb_group->currentData().toInt());
    m_examinee->setSubGroup(ui->cb_subGroup->currentData().toInt());
    m_examinee->setRang(ui->cb_rang->currentData().toInt());
    m_examinee->setDepartment(ui->cb_department->currentData().toInt());
    m_examinee->setSurname(ui->line_surname->text());
    m_examinee->setName(ui->line_name->text());
    m_examinee->setMiddleName(ui->line_middleName->text());
    m_examinee->setBorn(QDate::fromString(ui->line_born->text(), "dd.MM.yyyy"));
    m_examinee->setDiagnos(ui->cb_diagnos->currentData().toInt());
    m_examinee->setDiseases(ui->text_diseases->toPlainText());
    m_examinee->setComments(ui->text_comments->toPlainText());

    mng->saveExaminee(m_examinee);
    return qMakePair(ui->cb_department->currentText(), m_examinee->id());
}

void FormExaminee::reset()
{
    if(m_examinee){
        int id = m_examinee->id();
        m_examinee->deleteLater();
        loadForm(id);
    } else {
        resetForm();
    }
}

void FormExaminee::loadForm(int baseId)
{
    auto mng = new ExamineeManager(this);
    m_examinee = mng->getExaminee(baseId);
    setFrom(m_examinee);
}

void FormExaminee::setDepartment(QString dep)
{
    ui->cb_department->setCurrentText(dep);
}

void FormExaminee::resetForm()
{
    if(m_examinee)
        delete m_examinee;

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
    auto dm = new DictionaryManager(this);
    dm->loadDictionary(DType::AgeGroups, ui->cb_ageGroup);
    dm->loadDictionary(DType::Groups, ui->cb_group);
    dm->loadDictionary(DType::SubGroups, ui->cb_subGroup);
    dm->loadDictionary(DType::Rangs, ui->cb_rang);
    dm->loadDictionary(DType::Departments, ui->cb_department);
    dm->loadDictionary(DType::Diagnosis, ui->cb_diagnos);
    dm->loadDictionary(DType::Subdivision, ui->cb_subdivision);
}

void FormExaminee::setFrom(Examinee *e)
{
    Misc::setBoxValue(e->ageGroup(), ui->cb_ageGroup);
    Misc::setBoxValue(e->testGroup(), ui->cb_group);
    Misc::setBoxValue(e->subGroup(), ui->cb_subGroup);
    Misc::setBoxValue(e->rang(), ui->cb_rang);
    Misc::setBoxValue(e->department(), ui->cb_department);
    Misc::setBoxValue(e->subdivision(), ui->cb_subdivision);
    Misc::setBoxValue(e->diagnos(), ui->cb_diagnos);

    ui->line_surname->setText(e->surname());
    ui->line_name->setText(e->name());
    ui->line_middleName->setText(e->middleName());
    ui->line_born->setText(e->born().toString("dd.MM.yyyy"));
    ui->dsb_weght->setValue(e->weight());

    ui->text_diseases->setPlainText(e->diseases());
    ui->text_comments->setPlainText(e->comments());
}

bool FormExaminee::checkDate(QLineEdit *bl)
{
    if(!QDate::fromString(bl->text(), "dd.MM.yyyy").isValid()){
        QMessageBox::information(this, "Неверная дата", "Введена неверная дата рождения, введите в формате дд.мм.гггг");
        return false;
    }
    return true;
}

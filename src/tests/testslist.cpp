#include "testslist.h"
#include "ui_testslist.h"

#include "testform.h"
#include "testsmanager.h"
#include "test.h"

#include <QMessageBox>

TestsList::TestsList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestsList)
{
    ui->setupUi(this);
    loadTests();
}

TestsList::~TestsList()
{
    delete ui;
}

void TestsList::on_btn_add_clicked()
{
    auto t = new TestForm(this);
    if(t->exec() == QDialog::Accepted)
        loadTests();
}

void TestsList::loadTests()
{
    ui->lw_testList->clear();
    auto tm = new TestsManager(this);
    auto l = tm->loadTests();

    for(const auto t : qAsConst(l)){
        auto item = new QListWidgetItem(ui->lw_testList);
        item->setText(QString("%1(%2, %3)").arg(t->name(), t->subgroupName(), t->ageGroupName()));
        item->setData(Qt::UserRole, t->id());
        ui->lw_testList->addItem(item);
    }

    qDeleteAll(l);
}

int TestsList::getId()
{
    auto item = ui->lw_testList->currentItem();
    if(item == nullptr){
        QMessageBox::information(this, "Не выбрано", "Не выбран тест");
        return -1;
    }

    auto id = item->data(Qt::UserRole).toInt();
    return id;
}

void TestsList::on_btn_delete_clicked()
{
    auto id = getId();
    if(id == -1)
        return;

    int answer = QMessageBox::question(this, "Удаление теста", "Удалить тест?");
    if(answer == QMessageBox::No)
        return;

    auto tm = new TestsManager(this);
    tm->deleteTest(id);
    loadTests();
}


void TestsList::on_btn_edit_clicked()
{
    auto id = getId();
    if(id == -1)
        return;

    auto tf = new TestForm(this);
    tf->load(id);
    if(tf->exec() == QDialog::Accepted)
        loadTests();
    tf->deleteLater();
}


void TestsList::on_lw_testList_itemDoubleClicked(QListWidgetItem *item)
{
    Q_UNUSED(item)
    on_btn_edit_clicked();
}


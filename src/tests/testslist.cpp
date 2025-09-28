#include "testslist.h"
#include "ui_testslist.h"

#include "testform.h"

TestsList::TestsList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestsList)
{
    ui->setupUi(this);
}

TestsList::~TestsList()
{
    delete ui;
}

void TestsList::selectTests()
{

}

void TestsList::on_btn_add_clicked()
{
    auto t = new TestForm(this);
    if(t->exec() == QDialog::Accepted)
        selectTests();
}


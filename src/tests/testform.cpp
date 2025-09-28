#include "testform.h"
#include "ui_testform.h"

#include "testexesise.h"

TestForm::TestForm(QWidget *parent, int testId) :
    QDialog(parent),
    ui(new Ui::TestForm)
{
    ui->setupUi(this);
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


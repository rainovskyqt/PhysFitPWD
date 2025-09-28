#include "testexesise.h"
#include "ui_testexesise.h"

TestExesise::TestExesise(QWidget *parent, int exesiseId) :
    QDialog(parent),
    ui(new Ui::TestExesise)
{
    ui->setupUi(this);
}

TestExesise::~TestExesise()
{
    delete ui;
}

void TestExesise::on_cb_max_currentIndexChanged(int index)
{
    ui->cb_min->setCurrentIndex(index);
}


void TestExesise::on_cb_min_currentIndexChanged(int index)
{
    ui->cb_max->setCurrentIndex(index);
}


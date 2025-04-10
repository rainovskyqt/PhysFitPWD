#include "examineelist.h"
#include "ui_examineelist.h"

ExamineeList::ExamineeList(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ExamineeList)
{
    ui->setupUi(this);
}

ExamineeList::~ExamineeList()
{
    delete ui;
}

void ExamineeList::on_btn_close_clicked()
{
    reject();
}


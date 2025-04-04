#include "formexaminee.h"
#include "ui_formexaminee.h"

FormExaminee::FormExaminee(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormExaminee)
{
    ui->setupUi(this);
}

FormExaminee::~FormExaminee()
{
    delete ui;
}

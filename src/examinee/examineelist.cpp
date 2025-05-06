#include "examineelist.h"
#include "ui_examineelist.h"

#include "examineemanager.h"
#include "department.h"

ExamineeList::ExamineeList(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ExamineeList)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex((int)Pages::Empty);

    connect(ui->btn_save, &QToolButton::clicked, ui->page_examinee, &FormExaminee::save);
    connect(ui->btn_reset, &QToolButton::clicked, ui->page_examinee, &FormExaminee::reset);
    loadDepatments();
}

ExamineeList::~ExamineeList()
{
    delete ui;
}

void ExamineeList::on_btn_close_clicked()
{
    reject();
}

void ExamineeList::on_btn_expand_clicked()
{
    ui->treeWidget->expandAll();
}

void ExamineeList::on_btn_collapse_clicked()
{
    ui->treeWidget->collapseAll();
}

void ExamineeList::loadDepatments()
{
    ui->treeWidget->clear();

    auto mng = new ExamineeManager(this);
    auto deps = mng->getDepartments();

    for(auto const &d : qAsConst(deps)){
        QTreeWidgetItem* parentItem = new QTreeWidgetItem(ui->treeWidget);
        parentItem->setText(0, d->name());
        parentItem->setData(0, Qt::UserRole, d->id());
        d->deleteLater();
    }

    mng->deleteLater();
}


void ExamineeList::on_btn_add_clicked()
{
    ui->stackedWidget->setCurrentIndex((int)Pages::Examinee);
}


#include "examineelist.h"
#include "ui_examineelist.h"

#include "examineemanager.h"

ExamineeList::ExamineeList(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ExamineeList)
{
    ui->setupUi(this);

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
    auto mng = new ExamineeManager(this);
    auto deps = mng->getDepartments();

    for(auto const &d : qAsConst(deps)){
        QTreeWidgetItem* parentItem = new QTreeWidgetItem(ui->treeWidget);
        parentItem->setText(0, d);
    }

    mng->deleteLater();
}


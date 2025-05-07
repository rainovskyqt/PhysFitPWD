#include "examineelist.h"
#include "ui_examineelist.h"

#include "examineemanager.h"
#include "department.h"

#include <QSet>
#include <QString>

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
    ui->tree_departments->expandAll();
}

void ExamineeList::on_btn_collapse_clicked()
{
    ui->tree_departments->collapseAll();
}

void ExamineeList::loadDepatments()
{
//    ui->treeWidget->clear();
    ui->tree_departments->clear();

    auto mng = new ExamineeManager(this);
    auto examinees = mng->examineeList();


    auto departments = examinees.uniqueKeys();
    std::sort(departments.begin(), departments.end());

    for(const QString& key : qAsConst(departments)) {
        QTreeWidgetItem* parentItem = new QTreeWidgetItem(ui->tree_departments);
        parentItem->setText(0, key);

        auto exam = examinees.values(key);
        QSet<QPair<QString, int>> staffUnique = QSet<QPair<QString, int>>::fromList(exam);

        for(const auto &value : qAsConst(staffUnique)) {
            QTreeWidgetItem* childItem = new QTreeWidgetItem(parentItem);
            childItem->setData(0, Qt::UserRole, qAsConst(value.second));
            childItem->setText(0, value.first);
        }
    }

    mng->deleteLater();
}

void ExamineeList::addExaminee()
{
    ui->stackedWidget->setCurrentIndex((int)Pages::Examinee);
    ui->page_examinee->loadForm(0);
}

void ExamineeList::on_btn_add_clicked()
{
    addExaminee();
}


void ExamineeList::on_tree_departments_itemClicked(QTreeWidgetItem *item, int column)
{
    auto id = item->data(0, Qt::UserRole).toInt();
    if(id){
        ui->stackedWidget->setCurrentIndex((int)Pages::Examinee);
        ui->page_examinee->loadForm(id);
    }
}


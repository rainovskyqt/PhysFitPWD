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

    connect(ui->btn_save, &QToolButton::clicked, this, &ExamineeList::saveExaminee);
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
            if(!value.second)
                continue;
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
    ui->page_examinee->setDepartment(ui->tree_departments->currentItem()->text(0));
}

void ExamineeList::selectExaminee(QString dep, int id)
{
    for(int i = 0; i < ui->tree_departments->topLevelItemCount(); ++i){
        auto item = ui->tree_departments->topLevelItem(i);
        if(item->text(0) != dep){
            continue;
        }

        for(int j = 0; j < item->childCount(); ++j){
            auto child = item->child(j);
            if(child->data(0, Qt::UserRole).toInt() == id){
                child->setSelected(true);
                item->setExpanded(true);
                break;
            }
        }
    }
}

void ExamineeList::on_btn_add_clicked()
{
    addExaminee();
}

void ExamineeList::saveExaminee()
{
    QPair<QString, int> id = ui->page_examinee->save();
    if(id.second){
        loadDepatments();
        selectExaminee(id.first, id.second);
    }
}

void ExamineeList::on_tree_departments_itemClicked(QTreeWidgetItem *item, int column)
{
    auto id = item->data(0, Qt::UserRole).toInt();
    if(id){
        ui->stackedWidget->setCurrentIndex((int)Pages::Examinee);
        ui->page_examinee->loadForm(id);
    } else {
        ui->stackedWidget->setCurrentIndex((int)Pages::Empty);
    }
}


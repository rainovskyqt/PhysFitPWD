#ifndef EXAMINEELIST_H
#define EXAMINEELIST_H

#include <QDialog>
#include <QTreeWidgetItem>

namespace Ui {
class ExamineeList;
}

class ExamineeList : public QDialog
{
    Q_OBJECT

public:
    explicit ExamineeList(QWidget *parent = nullptr);
    ~ExamineeList();

private slots:
    void on_btn_close_clicked();
    void on_btn_expand_clicked();
    void on_btn_collapse_clicked();

    void on_btn_add_clicked();
    void on_tree_departments_itemClicked(QTreeWidgetItem *item, int column);

private:

    enum class Pages{
        Empty,
        Examinee
    };

    Ui::ExamineeList *ui;

    void loadDepatments();
    void addExaminee();
};

#endif // EXAMINEELIST_H

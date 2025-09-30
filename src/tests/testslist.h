#ifndef TESTSLIST_H
#define TESTSLIST_H

#include <QListWidgetItem>
#include <QWidget>

namespace Ui {
class TestsList;
}

class TestsList : public QWidget
{
    Q_OBJECT

public:
    explicit TestsList(QWidget *parent = nullptr);
    ~TestsList();

private slots:
    void on_btn_add_clicked();
    void on_btn_delete_clicked();
    void on_btn_edit_clicked();
    void on_lw_testList_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::TestsList *ui;

    void loadTests();
    int getId();
};

#endif // TESTSLIST_H

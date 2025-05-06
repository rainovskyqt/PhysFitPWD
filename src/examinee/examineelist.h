#ifndef EXAMINEELIST_H
#define EXAMINEELIST_H

#include <QDialog>

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

private:

    enum class Pages{
        Empty,
        Examinee
    };

    Ui::ExamineeList *ui;

    void loadDepatments();
};

#endif // EXAMINEELIST_H

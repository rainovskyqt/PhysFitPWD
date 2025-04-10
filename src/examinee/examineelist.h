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

private:
    Ui::ExamineeList *ui;
};

#endif // EXAMINEELIST_H

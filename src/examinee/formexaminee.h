#ifndef FORMEXAMINEE_H
#define FORMEXAMINEE_H

#include <QWidget>

namespace Ui {
class FormExaminee;
}

class FormExaminee : public QWidget
{
    Q_OBJECT

public:
    explicit FormExaminee(QWidget *parent = nullptr);
    ~FormExaminee();

private:
    Ui::FormExaminee *ui;
};

#endif // FORMEXAMINEE_H

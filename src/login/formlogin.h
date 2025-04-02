#ifndef FORMLOGIN_H
#define FORMLOGIN_H

#include <QMainWindow>

class User;

namespace Ui {
class FormLogin;
}

class FormLogin : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormLogin(QWidget *parent = nullptr);
    ~FormLogin();

signals:
    void succesLogin(User*);


private slots:
    void on_btn_close_clicked();
    void on_btn_enter_clicked();

private:
    Ui::FormLogin *ui;

    User* checkLogin(QString login, QString password);

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // FORMLOGIN_H

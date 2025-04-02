#include "formlogin.h"
#include "ui_formlogin.h"

#include <QMessageBox>

#include "mainwindow.h"
#include "user/user.h"

FormLogin::FormLogin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormLogin)
{
    ui->setupUi(this);
}

FormLogin::~FormLogin()
{
    delete ui;
}

void FormLogin::on_btn_close_clicked()
{
    this->close();
}

User* FormLogin::checkLogin(QString login, QString password)
{
    auto u = new User();
    return u;
}

void FormLogin::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        on_btn_enter_clicked();
    } else {
        QWidget::keyPressEvent(event);
    }
}

void FormLogin::on_btn_enter_clicked()
{
    auto user = checkLogin(ui->line_login->text().simplified().toLower(),
                           ui->line_password->text());

    if(user != nullptr){
        MainWindow *w = new MainWindow(user);
        w->show();
        this->close();
    } else {
        QMessageBox::critical(this, "Ошибка входа", "Не верные логин или пароль");
    }
}


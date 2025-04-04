#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "user/user.h"

MainWindow::MainWindow(User *user, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_user = user;
    m_user->setParent(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_quit_triggered()
{
    qApp->exit();
}


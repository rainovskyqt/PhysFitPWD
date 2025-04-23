#include "mainmenu.h"
#include "ui_mainmenu.h"

#include "examinee/examineelist.h"
#include "dictionary/dictionaryform.h"

MainMenu::MainMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_btn_examineeBase_clicked()
{
    ExamineeList *l = new ExamineeList(this);
    l->exec();
}


void MainMenu::on_btn_dictionaries_clicked()
{
    DictionaryForm *d = new DictionaryForm(this);
    d->exec();
}


#include "mainmenu.h"
#include "ui_mainmenu.h"

#include "examinee/examineelist.h"
#include "dictionary/dictionaryform.h"
#include "tests/testseditor.h"

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
    l->deleteLater();
}


void MainMenu::on_btn_dictionaries_clicked()
{
    DictionaryForm *d = new DictionaryForm(this);
    d->exec();
    d->deleteLater();
}


void MainMenu::on_btn_testsEditor_clicked()
{
    TestsEditor *e = new TestsEditor(this);
    e->exec();
    e->deleteLater();
}


#include "testseditor.h"
#include "ui_testseditor.h"

#include <dictionary/dictionarymanager.h>

TestsEditor::TestsEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestsEditor)
{
    ui->setupUi(this);
    ui->w_exesises->setDictionary(Dictionary::Type::Exesise);
}

TestsEditor::~TestsEditor()
{
    delete ui;
}

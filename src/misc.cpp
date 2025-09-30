#include "misc.h"

Misc::Misc() {}

void Misc::setBoxValue(int val, QComboBox *box)
{
    int index = box->findData(val, Qt::UserRole);
    box->setCurrentIndex(index == -1 ? 0 : index);
}

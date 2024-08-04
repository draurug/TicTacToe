#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"
#include <QIntValidator>
SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    QIntValidator *intValidator = new QIntValidator(0, 100, this);
    ui->m_port->setValidator(intValidator);

}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

#include "InviteDialog.h"
#include "ui_InviteDialog.h"

InviteDialog::InviteDialog( QString playerName, QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::InviteDialog)
{
    ui->setupUi(this);

    ui->m_text->setText( "Player '" + playerName + "' Inviting You To Play." );
}

InviteDialog::~InviteDialog()
{
    delete ui;
}

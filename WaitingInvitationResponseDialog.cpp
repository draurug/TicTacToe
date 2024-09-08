#include "WaitingInvitationResponseDialog.h"
#include "ui_WaitingInvitationResponseDialog.h"
#include "Model.h"
#include "Logic.h"

WaitingInvitationResponseDialog::WaitingInvitationResponseDialog( std::string partnerName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaitingInvitationResponseDialog),
    m_partnerName(partnerName)
{
    ui->setupUi(this);

    ui->m_label->setText( QString::fromStdString("...waiting invitation response from " + m_partnerName) );

    connect( ui->m_cancelBtn, &QPushButton::released, this, [this]
    {
        modelInstance().logic().cancelInvitation( m_partnerName );
        reject();
    });
}

WaitingInvitationResponseDialog::~WaitingInvitationResponseDialog()
{
    delete ui;
}

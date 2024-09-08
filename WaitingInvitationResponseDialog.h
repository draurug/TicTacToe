#pragma once

#include <QDialog>

namespace Ui {
class WaitingInvitationResponseDialog;
}

class WaitingInvitationResponseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WaitingInvitationResponseDialog( std::string partnerName,  QWidget *parent = nullptr);
    ~WaitingInvitationResponseDialog();

private:
    Ui::WaitingInvitationResponseDialog *ui;
    std::string m_partnerName;
};


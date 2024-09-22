#pragma once

#include <QDialog>

namespace Ui {
class InviteDialog;
}

class InviteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InviteDialog( QString playerName, QWidget *parent = nullptr);
    ~InviteDialog();

private:
    Ui::InviteDialog *ui;
};


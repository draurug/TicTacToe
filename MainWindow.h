#pragma once

#include <QMainWindow>
#include "Scene.h"
#include <functional>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class WaitingInvitationResponseDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( std::function<void()> closeStandaloneTest, QWidget* parent = nullptr);
    ~MainWindow();

    void init();

    void closeEvent(QCloseEvent *event) override;

public slots:
    void onPlayerListChangedSlot( std::map<std::string,bool> );

private:
    Ui::MainWindow* ui;
    Scene *scene;

    std::function<void()>               m_closeStandaloneTest;

    WaitingInvitationResponseDialog*    m_waitingInvitationResponseDialog = nullptr;
};

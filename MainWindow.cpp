//v3

#include "MainWindow.h"
#include "SettingsDialog.h"
#include "ui_MainWindow.h"
#include "Scene.h"
#include "Model.h"
#include "Logic.h"
#include "WaitingInvitationResponseDialog.h"

#include <QDebug>
#include <QString>

MainWindow::MainWindow( std::function<void()> closeStandaloneTest, QWidget *parent )
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_closeStandaloneTest(closeStandaloneTest)
{
}

void MainWindow::init()
{
    ui->setupUi(this);
    connect( ui->m_scene, &Scene::onClick, &modelInstance().logic(), &Logic::onClick );
    connect( &modelInstance().logic(), &Logic::positionChanged, ui->m_scene, &Scene::positionChanged );
    connect( &modelInstance().logic(), &Logic::onPlayerListChangedSignal, this, &MainWindow::onPlayerListChangedSlot, Qt::QueuedConnection );

    connect( ui->m_settings, &QPushButton::released, this, [this]
    {
        SettingsDialog dialog(this);
        if(dialog.exec() == QDialog::Accepted)
        {
            qDebug() << "Accepted";
        }
    });

    connect( ui->m_inviteBtn, &QPushButton::released, this, [this]
    {
        auto* currentItem = ui->m_playerTable->currentItem();
        if ( currentItem == nullptr )
        {
            return;
        }

        auto playerName = ui->m_playerTable->currentItem()->text().toStdString();

        modelInstance().logic().sendInvitationTo( playerName );

        m_waitingInvitationResponseDialog = new WaitingInvitationResponseDialog( playerName );
        m_waitingInvitationResponseDialog->exec();
    });

    connect( &modelInstance().logic(), &Logic::onAcceptedInvitationSignal, this, [this] (auto parthnerName, bool isAccepted, bool myPlayerRoleIsX )
    {
        m_waitingInvitationResponseDialog->close();
        ui->m_scene->setMyPlayerRole( myPlayerRoleIsX );
    });


    connect( &modelInstance().logic(), &Logic::onPartnerStepSignal, this, [this] ( int x, int y, bool isX )
    {
        ui->m_scene->onPartnerStepSlot( x, y, isX );
    },
    Qt::QueuedConnection );


    ui->m_playerTable->setColumnWidth( 0, ui->m_playerTable->width() );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    modelInstance().logic().closeSocket();
    m_closeStandaloneTest();
    event->accept();
}

void MainWindow::onPlayerListChangedSlot( std::map<std::string,bool> playerList )
{
    ui->m_playerTable->setRowCount(0);

    for( const auto& playerInfo : playerList )
    {
        int rowCount = ui->m_playerTable->rowCount();
        ui->m_playerTable->insertRow(rowCount); // Insert a new row at the end

        // Set data for each cell in the new row
        if ( playerInfo.second )
        {
            ui->m_playerTable->setItem(rowCount, 0, new QTableWidgetItem( QString::fromStdString( playerInfo.first ) ));
        }
    }
}


//v1
// #include "MainWindow.h"
// #include "SettingsDialog.h"
// #include "ui_MainWindow.h"
// #include "Scene.h"
// #include "Settings.h"
// #include "Model.h"
// #include "Logic.h"
// #include <QDebug>

// MainWindow::MainWindow(QWidget* parent)
//     : QMainWindow(parent)
//     , ui(new Ui::MainWindow)
// {
//     ui->setupUi(this);
//     connect(ui->m_scene, &Scene::onClick, Model().logic(), &Logic::onClick);
//     connect(Model().logic(), &Logic::positionChanged, ui->m_scene, &Scene::positionChanged);
//     connect(ui->m_settings, &QPushButton::released, this, [this]
//             {
//                 SettingsDialog dialog(this);
//                 if(dialog.exec() == QDialog::Accepted)
//                 {
//                     qDebug() << "Accepted";
//                 }
//             });
//     // SettingsDialog settingsDialog;

//     // QFile settingsFile("settings.dat");

//     // if (!settingsFile.exists())
//     // {
//     //     // Показываем диалог настроек поверх основного окна
//     //     settingsDialog.exec();
//     // }
//     // else
//     // {
//     //     Settings settings;
//     //     settings.load();
//     // }
// }

// MainWindow::~MainWindow()
// {
//     delete ui;
// }

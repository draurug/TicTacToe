//v3

#include "MainWindow.h"
#include "SettingsDialog.h"
#include "ui_MainWindow.h"
#include "Scene.h"
#include "Model.h"
#include "Logic.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->m_scene, &Scene::onClick, model().logic(), &Logic::onClick);
    connect(model().logic(), &Logic::positionChanged, ui->m_scene, &Scene::positionChanged);
    connect(ui->m_settings, &QPushButton::released, this, [this]
            {
                SettingsDialog dialog(this);
                if(dialog.exec() == QDialog::Accepted)
                {
                    qDebug() << "Accepted";
                }
            });
}

MainWindow::~MainWindow()
{
    delete ui;
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

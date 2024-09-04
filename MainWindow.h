#pragma once

#include <QMainWindow>
#include "Scene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void init();

private:
    Ui::MainWindow* ui;
    Scene *scene;
};

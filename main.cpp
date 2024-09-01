//v3
#include <QApplication>
#include "MainWindow.h"
#include "SettingsDialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Создаем основное окно
    MainWindow mainWindow;
    mainWindow.show();

    // Создаем и открываем окно настроек
    SettingsDialog settingsDialog;
    settingsDialog.exec();

    // Запуск цикла обработки событий
    return app.exec();
}

//v1
// #include <QApplication> //was
// #include "MainWindow.h"

//     int main(int argc, char *argv[])
// {
//     QApplication app(argc, argv);

//     MainWindow mainWindow;
//     mainWindow.show();

//     return app.exec();
// }

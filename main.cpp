//v3
#include <QApplication>
#include "MainWindow.h"
#include "SettingsDialog.h"
#include "SettingsDialog.h"
#include "Settings.h"
#include "Model.h"

#ifdef STANDALONE_TEST
#include "TicTacTcpServer.h"
#include "DbgTicTacClient.h"
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if ( ! modelInstance().settings().load() )
    {
        // Создаем и открываем окно настроек
        SettingsDialog settingsDialog;
        settingsDialog.exec();
    }
    modelInstance().initLogic();

    // Создаем основное окно
    MainWindow mainWindow;
    mainWindow.show();
    mainWindow.init();

#ifdef STANDALONE_TEST
    tic_tac::TicTacServer server( "127.0.0.1", "15001" );
    std::thread( [&server] { server.run(); }).detach();

    usleep(1000);

    std::thread( []
    {
        tic_tac::DbgTicTacClient client( "Player0" );
        client.run( "127.0.0.1", "15001" );
    }).detach();

#endif

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

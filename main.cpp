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

#ifdef STANDALONE_TEST
    tic_tac::TicTacServer server( "127.0.0.1", "15001" );
    auto serverThread = std::thread( [&server] { server.run(); });

    usleep(1000);

    tic_tac::DbgTicTacClient client( "Player2" );

    auto clientThread = std::thread( [&]
    {
        client.run( "127.0.0.1", "15001" );
    });
#endif

    // Создаем основное окно
    MainWindow mainWindow( [&]
    {
#ifdef STANDALONE_TEST
        server.shutdown();
        client.closeSocket();

        if ( clientThread.joinable() )
        {
            clientThread.join();

        }
        serverThread.join();
#endif
    });
    mainWindow.show();
    mainWindow.init();

    modelInstance().startTcpClient();

    // Запуск цикла обработки событий
    int rc = app.exec();
    return rc;
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

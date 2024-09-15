#pragma once

#include <QObject>
#include <QVector>
#include <QDebug>

#define LOG(expr) qDebug() << expr;
#define LOG_ERR(expr) qCritical() << expr;

#include "TicTacClient.h"

static const int GRID_SIZE = 3;
static_assert( GRID_SIZE == 3 ); // must be same as in Scene

class Logic : public QObject, public tic_tac::TicTacClient
{
    Q_OBJECT

    enum CurrentState {
        cst_initial,
        cst_handshaking,
        cst_waiting_user_choice,
        cst_inviting,
        cst_gaming,
        cst_game_ending,
    };


    int m_grid[GRID_SIZE][GRID_SIZE] = {0};

    std::string m_playerName;
    std::thread m_thread;

    CurrentState m_currentState = cst_initial;
    std::string  m_otherPlayerName;

    bool         m_playerRoleX = false;

public:
    Logic( std::string playerName ) : tic_tac::TicTacClient(playerName), m_playerName(playerName)
    {}

    void runTcpClient( std::string addr, std::string port )
    {
        m_thread = std::thread( [this]
        {
            tic_tac::TicTacClient::run( "127.0.0.1", "15001" );
        });
    }

    void closeTcpClient( std::string addr, std::string port )
    {
        closeSocket();
        m_thread.join();
    }

    void sendInvitationTo( std::string playerName );

    void cancelInvitation( std::string partnerName );


protected:
    virtual void onRegistered() override;

    virtual void onPlayerListChanged() override;

    virtual void onInvitation( std::string playName ) override {}

    virtual void onAcceptedInvitation( std::string playName, bool isAccepted ) override;

    virtual void onPlayerOfflined( std::string playName ) override {}

    virtual void onPartnerStep( bool isX, int x, int y ) override;


public slots:
    void onClick(int x, int y, int value);

signals:
    void positionChanged( QVector<int> ); // Объявляем сигнал с массивом
    void onPlayerListChangedSignal( std::map<std::string,bool> );
    void onAcceptedInvitationSignal( std::string playerName, bool isAccepted, bool myPlayerRoleIsX );
    void onPartnerStepSignal( int x, int y, bool isX );
};

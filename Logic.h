#pragma once

#include <QObject>
#include <QVector>
#include <QDebug>

#define LOG(expr) qDebug() << expr;
#define LOG_ERR(expr) qCritical() << expr;

#include "TicTacClient.h"

class Logic : public QObject, public tic_tac::TicTacClient
{
    Q_OBJECT

    static const int GRID_SIZE = 3;
    int m_grid[GRID_SIZE][GRID_SIZE] = {0};

    std::string m_playerName;

public:
    Logic( std::string playerName ) : tic_tac::TicTacClient(playerName), m_playerName(playerName)
    {}

    void runTcpClient( std::string addr, std::string port )
    {
        std::thread( [this]
        {
            tic_tac::TicTacClient::run( "127.0.0.1", "15001" );
        }).detach();
    }

protected:
    virtual void onPlayerListChanged() override {
        LOG( "m_availablePlayList: " << m_availablePlayList.size() );
        LOG( "m_availablePlayList: " << m_availablePlayList.size() );
    }

    // returned 'true'  -> if invitation accepted
    // returned 'false' -> if invitation rejected
    virtual bool onInvitation( std::string playName ) override { return true; }

    // if 'isAccepted' and returned 'false' -> 'close game'
    // if 'isAccepted' and returned 'true' -> 'game started'
    // if '!isAccepted' and returned 'false' -> client go to state 'cst_waiting_user_choice'
    // if '!isAccepted' and returned 'true' -> client stays in state 'cst_inviting' (in case 2 or more player were invited by us)
    virtual bool onAcceptedInvitation( std::string playName, bool isAccepted ) override { return true; }

    // returned 'false' -> client go to state 'cst_waiting_user_choice'
    // returned 'true' -> client stays in current state
    virtual bool onPlayerOfflined( std::string playName ) override { return true; }

    virtual void onPartnerStep( bool isX, int x, int y ) override {}


public slots:
    void onClick(int x, int y, int value);

signals:
    void positionChanged(QVector<int>); // Объявляем сигнал с массивом
};

#include "Logic.h"
#include "InviteDialog.h"
#include <QVector>
#include <QTimer>
#include <QMessageBox>

Logic::Logic( std::string playerName ) : tic_tac::TicTacClient(playerName), m_playerName(playerName)
{
    m_currentState = cst_handshaking;

    connect( this, &Logic::runOnMainThread, this, [] (std::function<void()> f) {f();}, Qt::QueuedConnection );

//    connect( this, &Logic::onInviteSignal, this, [this] ( std::string playerName )
//    {
//        InviteDialog dialog( QString::fromStdString(playerName) );
//        int rc = dialog.exec();

//        if ( rc == QDialog::Accepted )
//        {
//            sendInvitaionResponse( playerName, true );
//            m_currentState = cst_gaming;
//            QMessageBox::information( nullptr, "Make Step", "Make your 1-st step" );
//        }
//        else
//        {
//            sendInvitaionResponse( playerName, false );
//            m_currentState = cst_waiting_user_choice;
//        }
//    },
//    Qt::QueuedConnection );
}

void Logic::onClick(int x, int y, int value)
{
    if (x >= 0 && x <=3 && y >=0 && y <=3 )
    {
        if (m_mainGrid[x][y] == 0)
        {
            m_mainGrid[x][y] = value;
            QVector<int> vector;
            for( int i = 0; i < 3; i++)
            {
                for( int j= 0; j < 3; j++)
                {
                    vector.push_back(m_mainGrid[i][j]);
                }
            }
            emit positionChanged( vector, -1, -1 );
            sendStep( m_otherPlayerName, m_playerRoleX?"X":"0", std::to_string(x), std::to_string(y) );
        }

    }
}

void Logic::onRegistered()
{
    if ( m_currentState == cst_handshaking )
    {
        m_currentState = cst_waiting_user_choice;
    }
}


void Logic::sendInvitationTo( std::string playerName )
{
    m_currentState = cst_inviting;
    m_otherPlayerName = playerName;
    this->sendInvitaion( playerName );
}

void Logic::cancelInvitation( std::string partnerName )
{
    this->sendCloseGame( partnerName );
}

void Logic::onPlayerListChanged()
{
    LOG( "m_availablePlayerList: " << m_availablePlayerList.size() );
    emit onPlayerListChangedSignal( m_availablePlayerList );
}

void Logic::onInvitation( std::string playerName )
{
    if ( m_currentState == cst_waiting_user_choice || m_currentState == cst_handshaking )
    {
        m_currentState = cst_invite_responding;

        //emit onInviteSignal( playerName );
        emit runOnMainThread( [playerName,this]
        {
            InviteDialog dialog( QString::fromStdString(playerName) );
            int rc = dialog.exec();

            if ( rc == QDialog::Accepted )
            {
                sendInvitaionResponse( playerName, true );
                m_currentState = cst_gaming;
                QMessageBox::information( nullptr, "Make Step", "Make your 1-st step" );
            }
            else
            {
                sendInvitaionResponse( playerName, false );
                m_currentState = cst_waiting_user_choice;
            }
        });
    }
    else
    {
        sendInvitaionResponse( playerName, false );
    }
}

void Logic::onAcceptedInvitation( std::string playerName, bool isAccepted )
{
    if ( m_otherPlayerName != playerName || m_currentState != cst_inviting)
    {
        return;
    }

    emit onAcceptedInvitationSignal( playerName, isAccepted, false );

    if ( isAccepted )
    {
        m_currentState = cst_gaming;
    }
    else
    {
        m_currentState = cst_waiting_user_choice;
    }
}

void Logic::onPartnerStep( std::string parthnerName, bool isX, int x, int y )
{
    if ( m_currentState != cst_gaming )
    {
        return;
    }

    if ( x>=0 && x<=2 && y>=0 && y<=2 && m_mainGrid[x][y] == 0 )
    {
        if ( isX )
        {
            m_mainGrid[x][y] = 1;
        }
        else
        {
            m_mainGrid[x][y] = 2;
        }
    }
    emit onPartnerStepSignal( x, y, isX );
}

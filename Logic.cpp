#include "Logic.h"
#include <QVector>


void Logic::onClick(int x, int y, int value)
{
    if (x >= 0 && x <=3 && y >=0 && y <=3 )
    {
        if (m_grid[x][y] == 0)
        {
            m_grid[x][y] = value;
            QVector<int> vector;
            for( int i = 0; i < 3; i++)
            {
                for( int j= 0; j < 3; j++)
                {
                    vector.push_back(m_grid[i][j]);
                }
            }
            emit positionChanged (vector);
        }

    }
}

void Logic::onRegistered()
{
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

void Logic::onPartnerStep( bool isX, int x, int y )
{
    if ( m_currentState != cst_gaming )
    {
        return;
    }

    if ( x>=0 && x<=2 && y>=0 && y<=2 && m_grid[x][y] == 0 )
    {
        if ( isX )
        {
            m_grid[x][y] = 1;
        }
        else
        {
            m_grid[x][y] = 2;
        }
    }
    emit onPartnerStepSignal( x, y, isX );
}

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

void Logic::sendInvitationTo( std::string playerName )
{
    this->sendInvitaion( playerName );
}

void Logic::cancelInvitation( std::string partnerName )
{
    this->sendCloseGame( partnerName );
}

void Logic::onPlayerListChanged()
{
    LOG( "m_availablePlayList: " << m_availablePlayList.size() );
    emit onPlayerListChangedSignal( m_availablePlayList );
}

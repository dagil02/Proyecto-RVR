#include "GameManager.h"
#include "Chat.h"

using namespace std;

void GameManager::sendResults(){

}

void GameManager::selectionPhase()
{
}

int GameManager::mainGameLoop(){
}

void GameManager::battlePhase()
{
}

void GameManager::joinPlayers(PlayerInfo* playerone, PlayerInfo* playertwo, Socket* sockone, Socket* socktwo, Socket* socketMain) {
    
    player1->setAll(playerone->_id, playerone->_name);
    player2->setAll(playertwo->_id, playertwo->_name);
    playerInfo1 = playerone;
    playerInfo2 = playertwo;

    playerInfo1->_turnoJugador = 1;
    playerInfo2->_turnoJugador = 1;

    sock1 = sockone;
    sock2 = socktwo;

    socket = socketMain;

    sock1->send(*playerInfo1,*sock1);
    sock1->send(*playerInfo2,*sock1);
    sock2->send(*playerInfo2,*sock2);
    sock2->send(*playerInfo1,*sock2);
}


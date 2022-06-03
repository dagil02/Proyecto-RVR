#include "GameManager.h"
#include "ClientServer.h"


int GameManager::run(){

    while(true)
    {
        if (turnoJugador == 0){
            std::cout << "Esperando a jugador 1..." << std::endl;
            sock1->recv(*playerInfo1);

            // Enviamos al otro jugador la jugada realizada
            sock2->send(*playerInfo1,*sock2);

            turnoJugador = 1;
        }
        else{
            std::cout << "Esperando a jugador 2..." << std::endl;
            sock2->recv(*playerInfo2);

            // Enviamos al otro jugador la jugada realizada
            sock1->send(*playerInfo2,*sock1);

            turnoJugador = 0;
        }
    }

	return 0;
}

void GameManager::updatePlayers(PlayerInfo* playerone, PlayerInfo* playertwo, Socket* sockone, Socket* socktwo, Socket* socketMain) {
    
    player1->setId(playerone->_id);
    player2->setId(playertwo->_id);

    playerInfo1 = playerone;
    playerInfo2 = playertwo;

    sock1 = sockone;
    sock2 = socktwo;

    socket = socketMain;
    
    sock1->send(*playerInfo1,*sock1);
    sock1->send(*playerInfo2,*sock1);
    sock2->send(*playerInfo2,*sock2);
    sock2->send(*playerInfo1,*sock2);
}   
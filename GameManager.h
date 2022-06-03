#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

#include <iostream>
#include <string>
#include <string.h>

#include "Socket.h"
#include "Serializable.h"

class PlayerInfo;

using namespace std;


class Player
{
protected:
    int _id;

public:
    Player() {}
    Player(int id)
    {
        _id = id;
    };
    ~Player(){};

    int getId() { return _id; };

    void setId(int newid) {
        _id = newid;
    }
};

class GameManager
{
private:
    Player *player1;
    Player *player2;
    PlayerInfo* playerInfo1;
    PlayerInfo* playerInfo2;

    Socket* sock1;
    Socket* sock2;

    Socket* socket;

    int turnoJugador = 0;

public:
    GameManager() {
        player1 = new Player(0);
        player2 = new Player(1);
       
    }
    ~GameManager()
    {
        delete player1;
        delete player2;
        delete sock1;
        delete sock2;
        delete socket;
    };
    
   
    int run();

    void updatePlayers(PlayerInfo* playerone, PlayerInfo* playertwo, Socket* sockone, Socket* socktwo, Socket* socketMain);
    
};
#endif
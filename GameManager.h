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
    string _name;

public:
    Player() {}
    Player(string nombre, int id)
    {
        _name = nombre;
        _id = id;
    };
    ~Player(){};

    int getId() { return _id; };
    string getName() { return _name; };

    
    void setId(int newid) {
        _id = newid;
    }

    void setAll(int id, string name) {
        _id = id;
        _name = name;
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

public:
    GameManager() {
        player1 = new Player("a", 0);
        player2 = new Player("b", 0);
       
    }
    ~GameManager()
    {
        delete player1;
        delete player2;
        delete sock1;
        delete sock2;
        delete socket;
      


    };
    //Devuelve la situación de ambos jugadores
    void showStats(Player *player)
    {
        cout << player->getName() << " Vidas: " << player->getHealth() << " Balas: " << player->getAmmo() << " Cervezas: " << player->getBeer() << endl;
    }

    void sendResults();
    //Para seleccionar la acción
    void selectionPhase();

    //Este método consiste en un switch enorme que contemplará todos los casos posibles a la hora de batirse en duelo
    void battlePhase();

    int mainGameLoop();

    void joinPlayers(PlayerInfo* playerone, PlayerInfo* playertwo, Socket* sockone, Socket* socktwo, Socket* socketMain);
    
};
#endif
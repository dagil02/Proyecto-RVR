#ifndef _GHAT_H
#define _CHAT_H
#include <string>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <thread>
#include "Serializable.h"
#include "Socket.h"
#include "GameManager.h"
#include <iostream>

using namespace std;
using std::string;

class Client
{
public:
    Client(const char *s, const char *p) : socket(s, p){};
    virtual ~Client(){};

    void input_thread();

    void net_thread();

    Socket socket;
};

/////////////////////////////////////////////////////////////////////////////

class PlayerInfo : public Serializable
{

public:
    PlayerInfo() {}
    PlayerInfo(int id, string name, int jugada) : Serializable()
    {
        _id = id;
        _name = name;
        _jugada = jugada;
    }

    void to_bin();
    int from_bin(char *data);

    int _id;
    string _name;
    int _jugada;

    static const size_t MESSAGE_SIZE = sizeof(uint8_t) * 6 + sizeof(char) * 8;
};

class ClientPlayer : public Player, public Client
{
public:
    ClientPlayer(const char *s, const char *p, const char *n, int id) : Player(n, id), Client(s, p) {}

    virtual void login()
    {
        connect(socket.sd, &socket.sa, socket.sa_len);
        pi = new PlayerInfo(_id, _name,-1);
        socket.send(*pi, socket);
        piEnemy = new PlayerInfo(0, "",-1);
    }

    void waitForInput()
    {
        /*Socket *outsocket;
        do
        {
            socket.recv(*pi, outsocket);
            socket.recv(*piEnemy, outsocket);
        } while (pi->_turnoJugador == 0);*/
    }

    void input(int jugada)
    {
    	pi->_jugada = jugada;
        socket.send(*pi, socket);
    }

    bool update(int enviar)
    {
        return false;
    }

    PlayerInfo *pi;
    PlayerInfo *piEnemy;
    bool win = false;
    bool pulsado = false;
};

////////////////////////////////////////////////////////////

class Server
{
public:
    Server(const char *s, const char *p) : socket(s, p), gm()
    {
        int aux;
        aux = socket.bind();
    };

    bool accept_players();

private:

    ClientPlayer *client1;
    ClientPlayer *client2;

    GameManager *gm;
    Socket socket;
};
#endif
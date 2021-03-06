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


class PlayerInfo : public Serializable
{
public:
    PlayerInfo() {}
    PlayerInfo(int id, int columnaSeleccionada, bool miTurno) : Serializable()
    {
        _id = id;
        _columnaSeleccionada = columnaSeleccionada;
        _miTurno = miTurno;
    }

    void to_bin();
    int from_bin(char *data);

    int _id;
    int _columnaSeleccionada;
    bool _miTurno;

    static const int32_t MESSAGE_SIZE = sizeof(int) * 2 + sizeof(bool);
};


class Client
{
public:
    Client(const char *s, const char *p) : socket(s, p){};
    virtual ~Client(){};

    Socket socket;
};


class ClientPlayer : public Player, public Client
{
public:
    ClientPlayer(const char *s, const char *p, int id) : Player(id), Client(s, p) {}

    virtual void login()
    {
        connect(socket.sd, &socket.sa, socket.sa_len);
        pi = new PlayerInfo(_id, -1, false);
        socket.send(*pi, socket);
        piEnemy = new PlayerInfo(0, -1, false);
    }

    bool waitForMessage()
    {
        Socket *outsocket;

        if (!partidaEmpezada)
        {
            socket.recv(*pi, outsocket);
            socket.recv(*piEnemy, outsocket);
            std::cout << "---- Partida Empezada ----" << std::endl;

            partidaEmpezada = true;
            return false;
        }

        while (!pi->_miTurno)
        {
            socket.recv(*piEnemy, outsocket);
            return true;
        }

        return false;
    }

    void sendMessage()
    {
        socket.send(*pi, socket);
    }

    bool update()
    {
        return waitForMessage();
    }

    PlayerInfo *pi;
    PlayerInfo *piEnemy;
    bool partidaEmpezada = false;
};


class Server
{
public:
    Server(const char *s, const char *p) : socket(s, p), gm()
    {
        int aux;
        aux = socket.bind();
    };

    bool waitForPlayersConnection();

private:

    ClientPlayer *client1;
    ClientPlayer *client2;

    GameManager *gm;
    Socket socket;
};
#endif
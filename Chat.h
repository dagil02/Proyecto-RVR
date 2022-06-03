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
    PlayerInfo(int id, string name, int columnaSeleccionada, bool miTurno) : Serializable()
    {
        _id = id;
        _name = name;
        _columnaSeleccionada = columnaSeleccionada;
        _miTurno = miTurno;
    }

    void to_bin();
    int from_bin(char *data);

    int _id;
    string _name;
    int _columnaSeleccionada;
    bool _miTurno;

    static const size_t MESSAGE_SIZE = sizeof(uint8_t) * 2 + sizeof(char) * 8 + sizeof(bool);
};

class ClientPlayer : public Player, public Client
{
public:
    ClientPlayer(const char *s, const char *p, const char *n, int id) : Player(n, id), Client(s, p) {}

    virtual void login()
    {
        connect(socket.sd, &socket.sa, socket.sa_len);
        pi = new PlayerInfo(_id, _name, -1, false);
        std::cout << "NOMBRE: " << pi->_name << std::endl;
        socket.send(*pi, socket);
        piEnemy = new PlayerInfo(0, "", -1, false);
    }

    void waitForMessage()
    {
        Socket *outsocket;
        do
        {
            socket.recv(*pi, outsocket);
            std::cout << "MESSAGE RECIEVED playerID: " << pi->_id << std::endl;
            socket.recv(*piEnemy, outsocket);
        } while (pi->_miTurno);
    }

    void sendMessage(int jugada)
    {
    	pi->_columnaSeleccionada = jugada;
        socket.send(*pi, socket);
    }

    bool update(int enviar)
    {
        waitForMessage();

        return false;
    }

    PlayerInfo *pi;
    PlayerInfo *piEnemy;
    bool win = false;
    bool turno = false;
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
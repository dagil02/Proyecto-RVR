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
    PlayerInfo(int id, string name, int health, int ammo, int beer, int action) : Serializable()
    {
        _id = id;
        _name = name;
        _health = health;
        _beer = beer;
        _ammo = ammo;
        _action = action;
        _turnoJugador = 0;
    }

    void to_bin();
    int from_bin(char *data);

    int _id;
    string _name;
    int _health;
    int _beer;
    int _ammo;
    int _action;
    int _turnoJugador;

    static const size_t MESSAGE_SIZE = sizeof(uint8_t) * 6 + sizeof(char) * 8;
};

class ClientPlayer : public Player, public Client
{
public:
    ClientPlayer(const char *s, const char *p, const char *n, int id) : Player(n, id), Client(s, p) {}

    virtual void login()
    {
        std::cout << "1" << std::endl;
        connect(socket.sd, &socket.sa, socket.sa_len);
        std::cout << "2" << std::endl;
        pi = new PlayerInfo(_id, _name, 0, 0, 0, 0);
        std::cout << "3" << std::endl;
        socket.send(*pi, socket);
        std::cout << "4" << std::endl;
        piEnemy = new PlayerInfo(0, "", 3, 0, 1, 5);
        std::cout << "5" << std::endl;
    }

    void waitForInput()
    {
        Socket *outsocket;
        do
        {
            socket.recv(*pi, outsocket);
            socket.recv(*piEnemy, outsocket);
        } while (pi->_turnoJugador == 0);
    }

    void input(int enviar)
    {
        pi->_action = enviar;
        socket.send(*pi, socket);
    }

    void showStats()
    {
        std::cout << "Vidas: " << pi->_health << " Balas: " << pi->_ammo << " Cervezas: " << pi->_beer << std::endl;
        std::cout << "Vidas: " << piEnemy->_health << " Balas: " << piEnemy->_ammo << " Cervezas: " << piEnemy->_beer << std::endl;
    }

    bool update(int enviar)
    {
        if (pulsado)
        {
            if (pi->_health > 0 && piEnemy->_health > 0)
            {

                waitForInput();

                showStats();
                input(enviar);

            }
            if (pi->_health == 0)
            {
                cout << "Has muerto. Game Over" << endl;
                win = false;
                return false;
            }
            else if (piEnemy->_health == 0)
            {
                cout << "Has ganado. Eres un máquina" << endl;
                win = true;
                return false;
            }
        }
        return true;
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
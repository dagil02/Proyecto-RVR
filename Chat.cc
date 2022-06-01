#include "Chat.h"

bool Server::accept_players()
{
    listen(socket.sd, 16);
    gm = new GameManager();
    PlayerInfo obj(0, "");
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(struct sockaddr_in);

    int sd_client1 = accept(socket.sd, (struct sockaddr *)&client_addr, &client_len);
    std::cout << "Conexion desde IP: " << inet_ntoa(client_addr.sin_addr) << " PUERTO: " << ntohs(client_addr.sin_port) << std::endl;
    Socket *sock1 = new Socket((struct sockaddr *)&client_addr, client_len);
    sock1->sd = sd_client1;
    socket.recvInit(obj, sock1);
    PlayerInfo *newplayer1 = new PlayerInfo(0,obj._name);
    std::cout << newplayer1->_name << " se ha conectado" << std::endl;

    int sd_client2 = accept(socket.sd, (struct sockaddr *)&client_addr, &client_len);
    std::cout << "Conexion desde IP: " << inet_ntoa(client_addr.sin_addr) << " PUERTO: " << ntohs(client_addr.sin_port) << std::endl;
    Socket *sock2 = new Socket((struct sockaddr *)&client_addr, client_len);
    sock2->sd = sd_client2;
    socket.recvInit(obj, sock2);
    PlayerInfo *newplayer2 = new PlayerInfo(1, obj._name);
    std::cout << newplayer2->_name << " se ha conectado" << std::endl;

    gm->joinPlayers(newplayer1, newplayer2, sock1, sock2, &socket);

    gm->mainGameLoop();
    return false;
}

/////////////////////////////////////////////////////////////////////////////

void Client::input_thread()
{
  /*  while (true)
    {
        std::string msg;
        std::getline(std::cin, msg);

        ChatMessage em("jose", msg);
        em.type = ChatMessage::MESSAGE;

        int cosa = socket.send(em, socket);
    }*/
}

void Client::net_thread()
{/*
    while (true)
    {
        ChatMessage em;

        socket.recv(em);

        std::cout << &em.nick[0] << ": " << &em.message[0] << std::endl;
    }*/
}

////////////////////////////////////////////////////////////////////////////

void PlayerInfo::to_bin()
{
    
}

int PlayerInfo::from_bin(char *data)
{
    
    return 0;
}

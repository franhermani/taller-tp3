#ifndef SERVER_PROXY_H
#define SERVER_PROXY_H

class ServerProxy {
public:
    void interactWithClient();

    void receiveMessage();

    void sendMessage();
};

#endif // SERVER_PROXY_H

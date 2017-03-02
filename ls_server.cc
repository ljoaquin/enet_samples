#include <stdio.h>
#include <enet/enet.h>

int main(int argc, char const *argv[])
{
    if (enet_initialize() != 0)
    {
        fprintf(stderr, "An error occurred while initializing ENet.\n");
        return EXIT_FAILURE;
    }

    start();

    atexit(enet_deinitialize);
    return 0;
}

void start()
{
    ENetAddress address;
    ENetHost* server;

    address.host = ENET_HOST_ANY;
    address.port = 12345;
    server = enet_host_create(&address, 2, 2, 0, 0);
    if(server == NULL)
    {
        fprintf(stderr, "An error occurred while trying to create an ENet server host.\n");
        exit(EXIT_FAILURE);
    }

    ENetEvent event;
    while(enet_host_services(server, &event, 0) >= 0)
    {
        switch(event.type)
        {
            case ENET_EVENT_TYPE_CONNECT:
            {
                break;
            }
            case ENET_EVENT_TYPE_CONNECT:
            {
                break;
            }
            case ENET_EVENT_TYPE_CONNECT:
            {
                break;
            }
            default:
            {
                
                break;
            }
        }
    }
}

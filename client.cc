#include <stdio.h>
#include <string.h>
#include <enet/enet.h>

void test();

int main(int argc, char const *argv[])
{
    if (enet_initialize () != 0)
    {
        fprintf (stderr, "An error occurred while initializing ENet.\n");
        return EXIT_FAILURE;
    }

    test();

    atexit (enet_deinitialize);
    return 0;
}

ENetPeer* connect(ENetHost *client);
void send(ENetHost *client, ENetPeer *peer);
void disconnect(ENetHost *client, ENetPeer *peer);

void test()
{
    ENetHost * client;
    client = enet_host_create (NULL /* create a client host */,
                1 /* only allow 1 outgoing connection */,
                2 /* allow up 2 channels to be used, 0 and 1 */,
                57600 / 8 /* 56K modem with 56 Kbps downstream bandwidth */,
                14400 / 8 /* 56K modem with 14 Kbps upstream bandwidth */);
    if (client == NULL)
    {
        fprintf (stderr, 
                 "An error occurred while trying to create an ENet client host.\n");
        exit (EXIT_FAILURE);
    }

    ENetPeer *peer = connect(client);

    send(client, peer);

    disconnect(client, peer);

    enet_host_destroy(client);
}

ENetPeer* connect(ENetHost *client)
{
    ENetAddress address;
    ENetEvent event;
    /* Connect to 127.0.0.1:12345. */
    enet_address_set_host (& address, "127.0.0.1");
    address.port = 12345;
    /* Initiate the connection, allocating the two channels 0 and 1. */
    ENetPeer* peer = enet_host_connect (client, & address, 2, 0);    
    if (peer == NULL)
    {
       fprintf (stderr, 
                "No available peers for initiating an ENet connection.\n");
       exit (EXIT_FAILURE);
    }
    /* Wait up to 5 seconds for the connection attempt to succeed. */
    if (enet_host_service (client, & event, 5000) > 0 &&
        event.type == ENET_EVENT_TYPE_CONNECT)
    {
        puts ("Connection to 127.0.0.1:12345 succeeded.");
        // ...
        // ...
        // ...
    }
    else
    {
        /* Either the 5 seconds are up or a disconnect event was */
        /* received. Reset the peer in the event the 5 seconds   */
        /* had run out without any significant event.            */
        enet_peer_reset (peer);
        puts ("Connection to 127.0.0.1:12345 failed.");
    }
    return peer;
}

void send(ENetHost *client, ENetPeer *peer)
{
    /* Create a reliable packet of size 7 containing "packet\0" */
    ENetPacket * packet = enet_packet_create ("packet", 
                                              strlen ("packet") + 1, 
                                              ENET_PACKET_FLAG_RELIABLE);
    /* Extend the packet so and append the string "foo", so it now */
    /* contains "packetfoo\0"                                      */
    enet_packet_resize (packet, strlen ("packetfoo") + 1);
    strcpy ((char *)& packet -> data [strlen ("packet")], "foo");
    /* Send the packet to the peer over channel id 0. */
    /* One could also broadcast the packet by         */
    /* enet_host_broadcast (host, 0, packet);         */
    enet_peer_send (peer, 0, packet);
    // ...
    // ...
    // ...
    /* One could just use enet_host_service() instead. */
    enet_host_flush (client);
}

void disconnect(ENetHost *client, ENetPeer *peer)
{
    ENetEvent event;
    enet_peer_disconnect (peer, 0);
    /* Allow up to 3 seconds for the disconnect to succeed
     * and drop any packets received packets.
     */
    while (enet_host_service (client, & event, 3000) > 0)
    {
        switch (event.type)
        {
        case ENET_EVENT_TYPE_RECEIVE:
            enet_packet_destroy (event.packet);
            break;
        case ENET_EVENT_TYPE_DISCONNECT:
            puts ("Disconnection succeeded.");
            return;
        }
    }
    /* We've arrived here, so the disconnect attempt didn't */
    /* succeed yet.  Force the connection down.             */
    enet_peer_reset (peer);
}

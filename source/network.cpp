#include <stdio.h>
#include "network.h"

#define PLATFORM_WINDOWS  1
#define PLATFORM_MAC      2
#define PLATFORM_UNIX     3

#if defined(_WIN32)
#define PLATFORM PLATFORM_WINDOWS
#elif defined(__APPLE__)
#define PLATFORM PLATFORM_MAC
#else
#define PLATFORM PLATFORM_UNIX
#endif

#if PLATFORM == PLATFORM_WINDOWS
#include <winsock2.h>
#elif PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#endif



// scope file

bool initialize_sockets() {
    #if PLATFORM == PLATFORM_WINDOWS
        WSADATA WsaData;
        return WSAStartup(MAKEWORD(2,2), &WsaData) == NO_ERROR;
    #else
        return true;
    #endif
}


// scope export

// Address
// ---------------------------------------------------------------------------
Address::Address() {

}

Address::Address(uint32_t address, uint16_t port) {
    this->address = address;
    this->port = port;
}

Address::Address(uint8_t a, 
        uint8_t b, 
        uint8_t c, 
        uint8_t d, 
        uint16_t port)
{ 
    address = (a << 24 ) | (b << 16) | (c << 8) | d;
    this->port = port;
} 

uint8_t Address::a() {
    return (uint8_t)(address >> 24);
}

uint8_t Address::b() {
    return (uint8_t)(address >> 16);
}

uint8_t Address::c() {
    return (uint8_t)(address >> 8);
}

uint8_t Address::d() {
    return (uint8_t)address;
}

void Address::print_address() {
   printf("%d.%d.%d.%d:%d", a(), b(), c(), d(), port);
}

// Socket
// ---------------------------------------------------------------------------
Socket::Socket() {
    bool initialized = initialize_sockets();
    if (!initialized) {
        printf("ERROR: Failed to create socket\n");
        return;
    }

    handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (handle <= 0) {
        printf("Failed to create socket\n");
    }
}

bool Socket::open(uint16_t port) {
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( (uint16_t)port );

    if ( bind(handle, (const sockaddr*) &address, sizeof(sockaddr_in)) < 0 )
    {
        printf( "ERROR: Failed to bind socket\n" );
        return false;
    }

    // set socket to non-blocking mode
    #if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
        int nonBlocking = 1;
        if (fcntl(handle, F_SETFL, O_NONBLOCK, nonBlocking) == -1) {
            printf("ERROR: Failed to set socket as non-blocking\n");
            return false;
        }
    #elif PLATFORM == PLATFORM_WINDOWS
        DWORD nonBlocking = 1;
        if (ioctlsocket(handle, FIONBIO, &nonBlocking) != 0 ) {
            printf("ERROR: Failed to set socket as non-blocking\n");
            return false;
        }
    #endif

    return true;
}

bool Socket::is_open() {
    uint8_t buf;
    int err = recv(handle, &buf, 1, MSG_PEEK);
    return err == -1 ? false : true;
}

bool Socket::send(const Address &destination, const void *data, int size) {
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(destination.address);
    addr.sin_port = htons(destination.port);

    int sent_bytes = sendto(handle, 
                            (const char*)data,
                            size,
                            0,
                            (sockaddr*)&addr,
                            sizeof(sockaddr_in));

    if (sent_bytes != size) {
        printf( "ERROR: Failed to send packet\n" );
        return false;
    }    

    return true;
}

int Socket::receive(Address &sender, void *data, int size) {
    #if PLATFORM == PLATFORM_WINDOWS
    typedef int socklen_t;
    #endif    
    
    sockaddr_in from;
    socklen_t from_length = sizeof(from);

    int num_bytes = recvfrom(handle,
                             (char*)data,
                             size,
                             0,
                             (sockaddr*)&from,
                             &from_length);

    if (num_bytes > 0) {
        sender.address = ntohl(from.sin_addr.s_addr);
        sender.port = ntohs(from.sin_port);
    }

    return num_bytes;
}

void Socket::close() {
    #if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
    ::close(handle);
    #elif PLATFORM == PLATFORM_WINDOWS
    closesocket(handle);
    #endif
}

Socket::~Socket() { 
    if ( is_open() ) {
        this->close();
    }

    #if PLATFORM == PLATFORM_WINDOWS
    WSACleanup();
    #endif
}


//void test_sockets() {
    //printf("\ntemp_main\n");

    //int port = 30000;
    //Socket socket;

    //if (!socket.open(port)) {
        //printf("Error: Failed to create socket! port: %d\n", port);
        //return;
    //}

    //const char data[] = "Hello Sailor!";
    //auto dest = Address(127,0,0,1,port);
    //socket.send(dest, data, sizeof(data));

    //// receive packets
    //while (1) {
        //Address sender;
        //unsigned char buffer[256];
        //int bytes_read = socket.receive(sender, buffer, sizeof(buffer));
        //if (bytes_read <= 0) break;

        //// process packet
        //printf("\nbytes_read: %d\npacket data as string: %s\n", bytes_read, buffer);
    //}
//}



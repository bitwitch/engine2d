#pragma once
#include <stdint.h>
struct Address {
    uint32_t address;
    uint16_t port;

    Address();
    Address(uint32_t address, uint16_t port);
    Address(uint8_t a, 
            uint8_t b, 
            uint8_t c, 
            uint8_t d, 
            uint16_t port);

    // these return the parts of the address
    //  a | b | c | d
    // 000.000.000.000
    uint8_t a();
    uint8_t b();
    uint8_t c();
    uint8_t d();
};

struct Socket {
    Socket();
    ~Socket();

    bool open(uint16_t port);

    void close();

    bool is_open();

    bool send(const Address &destination, const void *packet_data, int packet_size);

    int receive(Address &sender, void *data, int size);

private:
    int handle;
};


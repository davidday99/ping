#include <stdint.h>
#include <netinet/in.h>

typedef struct icmphdr {
    uint8_t type;
    uint8_t code;
    uint8_t cksum;
    uint32_t unused;

} icmphdr;


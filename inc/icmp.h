#ifndef _ICMP_H_ 
#define _ICMP_H_

#include <stdint.h>

#define ICMP_TYPE_ECHO 8
#define ICMP_STATIC_ID 0xCC
#define ICMP_ECHO_DATA_SZ 48
#define ICMP_ECHO_DATA_OFFSET sizeof(icmp_echo_hdr)
#define hton16(x) ((((x) & 0xFF) << 8) | (((x) & 0xFF00) >> 8))
#define hton32(x) ((((x) & 0xFF) << 24) | (((x) & 0xFF00) << 8) |  \
                    (((x) & 0xFF0000) >> 8) | (((x) & 0xFF000000) >> 24))

typedef struct __attribute__ ((packed)) {
    uint8_t type;
    uint8_t code;
    uint16_t cksum;
    uint16_t id;
    uint16_t seqnum;
} icmp_echo_hdr;

typedef union icmp_echo {
    icmp_echo_hdr header;
    uint8_t data[sizeof(icmp_echo_hdr) + ICMP_ECHO_DATA_SZ];
} icmp_echo;


icmp_echo *get_icmp_echo_msg(uint16_t id, uint16_t seqnum);
void free_icmp_echo(icmp_echo *p); 

#endif /* _ICMP_H_ */

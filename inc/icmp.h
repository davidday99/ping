#ifndef _ICMP_H_ 
#define _ICMP_H_

#include <stdint.h>

#define ICMP_TYPE_ECHO 8
#define ICMP_STATIC_ID 0xCC
#define ICMP_ECHO_DATA_SZ 48
#define ICMP_ECHO_DATA_OFFSET sizeof(icmp_echo_hdr)

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

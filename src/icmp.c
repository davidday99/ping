#include <stdint.h>
#include <netinet/in.h>
#include <stdlib.h>
#include "icmp.h"
#include "in_cksum.h"

icmp_echo *get_icmp_echo_msg(uint16_t id, uint16_t seqnum) {
    icmp_echo *msg = malloc(sizeof(icmp_echo));
    msg->header.type = ICMP_TYPE_ECHO;
    msg->header.code = 0;
    msg->header.id =  hton16(id);
    msg->header.seqnum = hton16(seqnum);
    msg->header.cksum = 0;

    for (int i = 0; i < ICMP_ECHO_DATA_SZ; i++) {
        msg->data[ICMP_ECHO_DATA_OFFSET + i] = 0x30 + i; 
    }

    msg->header.cksum = csum((uint16_t *) msg->data, sizeof(icmp_echo));

    return msg;
}

void free_icmp_echo(icmp_echo *p) {
    free(p);
}


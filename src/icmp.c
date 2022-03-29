#include <stdint.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include "icmp.h"
#include "in_cksum.h"

void init_icmp_echo(icmp_echo *msg, uint16_t id, uint16_t seqnum) {
    msg->header.type = ICMP_TYPE_ECHO;
    msg->header.code = 0;
    msg->header.id =  htons(id);
    msg->header.seqnum = htons(seqnum);
    msg->header.cksum = 0;

    for (int i = 0; i < ICMP_ECHO_DATA_SZ; i++) {
        msg->data[ICMP_ECHO_DATA_OFFSET + i] = 0x30 + i; 
    }

    msg->header.cksum = csum((uint16_t *) msg->data, sizeof(icmp_echo));
}

char verify_icmp_echo_reply(icmp_echo *sent, icmp_echo *recv) {
    if (sent->header.id != recv->header.id ||
        sent->header.seqnum != recv->header.seqnum ||
        recv->header.type != ICMP_TYPE_ECHO_REPLY ||
        memcmp(&sent->data[ICMP_ECHO_DATA_OFFSET], 
               &recv->data[ICMP_ECHO_DATA_OFFSET], 
               ICMP_ECHO_DATA_SZ) != 0) {
        return 0;
    }
    return 1;
}

void increment_icmp_echo_seqnum(icmp_echo *echo) {
    uint16_t seqnum = ntohs(echo->header.seqnum);
    seqnum++;
    echo->header.seqnum = htons(seqnum);
    echo->header.cksum = 0;
    echo->header.cksum = csum((uint16_t *) echo->data, sizeof(icmp_echo));
}


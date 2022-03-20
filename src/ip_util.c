#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include "icmp.h"
#include "in_cksum.h"

#define IP_ICMP_PROTOCOL 1

static struct in_addr get_src_interface_ip(void) {
    struct ifaddrs *src;
    struct in_addr srcin_addr;
    getifaddrs(&src);
    if (inet_aton(src->ifa_name, &srcin_addr) == 0) {
        printf("Could not get source interface name\n");
        exit(1);
    }
    return srcin_addr; 
}

struct ip *icmp_to_ip(struct in_addr dst, icmp_echo *icmp, uint16_t len) {
    static int ip_id;
    ip_id = ip_id > 0 ? ip_id + 1 : rand();
    struct ip *packet = malloc(sizeof(struct ip) + len);
    packet->ip_v = 4; 
    packet->ip_hl = 5;
    packet->ip_tos = 0;
    packet->ip_len = htons(20 + len);
    packet->ip_id = htons(ip_id);
    packet->ip_off = htons(IP_DF);
    packet->ip_ttl = 64;
    packet->ip_p = IP_ICMP_PROTOCOL;
    packet->ip_sum = 0;
    packet->ip_dst = dst;
//    packet->ip_src = get_src_interface_ip();
    packet->ip_src = (struct in_addr) {.s_addr = 0xc0a80142};
    memcpy(packet + packet->ip_hl * 4, icmp->data, len); 
    packet->ip_sum = csum((uint16_t *) packet, packet->ip_len);
 
    return packet;
}

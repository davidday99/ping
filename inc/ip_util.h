#ifndef _IP_UTIL_H_
#define _IP_UTIL_H_

#include <stdint.h>
#include "icmp.h"

struct ip *icmp_to_ip(struct in_addr dst, icmp_echo *icmp, uint16_t len); 

#endif /* _IP_UTIL_H_ */

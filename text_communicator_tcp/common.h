#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

#define MSG_LOGIN 1
#define MSG_TEXT  2
#define MSG_EXIT  3
#define MSG_ACK   4
#define MSG_FAIL  5 

#define MC_GROUP "239.0.0.1"
#define MC_PORT 6000
#define SERVER_PORT 4444

typedef struct {
    int type;            
    int length;          
    char value[1024];    
} tlv_packet_t;

#endif

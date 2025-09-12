#pragma once

typedef enum {
  NA_NULL = 0,
  NA_LOOPBACK,
  NA_BROADCAST,
  NA_IP,
} net_address_type_e;

typedef struct net_address_s {
public:
  net_address_type_e type;
  unsigned char      ip[4];
  unsigned short     port;
} net_address_t;
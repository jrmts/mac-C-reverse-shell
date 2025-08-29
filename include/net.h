#pragma once
#include <stdint.h>

/**
 * Parse a decimal port string into uint16_t (1..65535).
 * Returns 0 on success, -1 on failure.
 */
int parse_port(const char *s, uint16_t *out_port);

/**
 * Connect to host:port (IPv4). Returns a connected socket fd on success, -1 on failure.
 */
int connect_to_c2(const char *host, uint16_t port);

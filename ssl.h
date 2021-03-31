#ifndef __SSL_H
#define __SSL_H

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <string.h>

void
ssl_free_context (SSL*, SSL_CTX*);

void
ssl_init_openssl (void);

SSL_CTX*
ssl_create_context (void);

SSL*
ssl_create_ssl (SSL_CTX* context);

bool
ssl_connect_tcp_connection (SSL* ssl, int sockfd);

void
ssl_tcp_write (SSL* ssl, const char* data);

#endif

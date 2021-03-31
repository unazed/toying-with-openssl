#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "ssl.h"

void
ssl_free_context (SSL* ssl)
{
  puts ("freeing SSL object/context");
  SSL_CTX* ctx = SSL_get_SSL_CTX (ssl);
  int sfd = SSL_get_fd (ssl);
  if (ctx != NULL)
    SSL_CTX_free (ctx);
  if (ssl != NULL)
    SSL_free (ssl);
  if (sfd >= 0)
  {
    SSL_shutdown (ssl); /* pray that this returns 0 */
    close (sfd);
  }
}

void
ssl_init_openssl (void)
{
  SSL_library_init ();
  SSL_load_error_strings ();
  OpenSSL_add_all_algorithms();
}

SSL_CTX*
ssl_create_context (void)
{
  const SSL_METHOD* method = TLS_method ();
  SSL_CTX* context = SSL_CTX_new (method);

  if (context == NULL)
  {
    ERR_print_errors_fp (stderr);
    return NULL;
  }
  return context;
}

SSL*
ssl_create_ssl (SSL_CTX* context)
{
  SSL* ssl = SSL_new (context);
  if (ssl == NULL)
  {
    fputs ("SSL_new() failed", stderr);
    ssl_free_context (ssl);
    return NULL;
  }
  return ssl;
}

bool
ssl_connect_tcp_connection (SSL* ssl, int sockfd)
{
  SSL_set_fd (ssl, sockfd);
  int status = SSL_connect(ssl);
  if (status != 1)
  {
    SSL_get_error (ssl, status);
    ERR_print_errors_fp (stderr);
    return false;
  }
  return true;
}

void
ssl_tcp_write (SSL* ssl, const char* data)
{
  SSL_write (ssl, data, strlen (data));
}

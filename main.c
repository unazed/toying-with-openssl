#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h>
#include <string.h>
#include "ssl.h"
#include "tcp.h"

#define POLL_ERR         (-1)
#define POLL_EXPIRE      (0)

void
main (int argc, char** argv)
{
  SSL_CTX* ctx = ssl_create_context ();
  SSL* ssl = ssl_create_ssl (ctx);
  struct pollfd pfd;
  char pollin_data[65536];
  memset (pollin_data, 0, sizeof (pollin_data));

  if (ssl == NULL || ctx == NULL)
    goto out_ssl_free;
  puts ("created SSL context successfully");

  int sockfd = create_tcp_connection (argv[1], argv[2]);
  if (sockfd < 0)
  {
    printf ("failed to connect to %s:%s\n", argv[1], argv[2]);
    goto out_ssl_free;
  } else if (!ssl_connect_tcp_connection (ssl, sockfd))
  {
    puts ("failed to connect SSL socket");
    goto out_sock_close;
  }
  pfd.fd = sockfd;
  pfd.events = POLLIN;

  ssl_tcp_write (ssl, "GET / HTTP/1.1\r\n\r\n");
  puts ("sent data, entering polling region");

  while (true)
  {
    switch (poll (&pfd, 1, 1000))
    {
      case POLL_EXPIRE:
        puts ("polling...");
        break;
      case POLL_ERR:
        goto out_sock_shutdown;
      default:
        memset (pollin_data, 0, sizeof (pollin_data));
        if (!SSL_read (ssl, pollin_data, sizeof (pollin_data)))
        {
          puts ("received EOF/SSL_read() error, closing...");
          goto out_sock_shutdown;
        }
        printf ("received: %s\n", pollin_data);
    }
  }

out_sock_shutdown:
  SSL_shutdown (ssl);
out_sock_close:
  close (sockfd);
out_ssl_free:
  ssl_free_context (ssl, ctx);
}

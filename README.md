# toying-with-openssl
small, inefficient interface over OpenSSL/TCP

For future archival purposes. Not intended to be production-quality code, just my demonstration to myself that I can use OpenSSL to a degree.
And, for reference, to employ a test-server, create a server as follows (assuming OpenSSL is installed):

```
unazed@spectaculum /h/d/c/o/server_cert [1]> openssl req -x509 -newkey rsa:4096 -keyout key.pem -out cert.pem -days 365 -nodes
Generating a RSA private key
...
unazed@spectaculum /h/d/c/o/server_cert> ls
cert.pem  key.pem
unazed@spectaculum /h/d/c/o/server_cert> openssl s_server -port 1024 -key key.pem -cert cert.pem
Using default temp DH parameters
ACCEPT
...
```

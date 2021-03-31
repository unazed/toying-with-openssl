#!/bin/bash
icpc -o main main.c tcp.c ssl.c -lssl -lcrypto; ./main 127.0.0.1 1024

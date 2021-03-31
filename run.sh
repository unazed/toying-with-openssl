#!/bin/bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/unazed/intel/oneapi/compiler/2021.1.2/linux/compiler/lib/intel64_lin
icpc -fopenmp -o main main.c tcp.c ssl.c -lssl -lcrypto; ./main 127.0.0.1 1024

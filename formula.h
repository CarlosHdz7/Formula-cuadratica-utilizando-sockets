/*Esta libreria incluye todas las librerias necesarias para que nuestra aplicacion
funcione*/
#include <rpc/rpc.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <rpc/types.h>
#include <rpc/xdr.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define PORT_UDP_SERV 6000
#define PORT_UDP_CLI 6001

#include "formula.h"

struct ec {
	float a,b,c,x1,x2,entera,imaginaria;
};


main(int argc, char *argv[])
{
  int sockfd,n;
  struct sockaddr_in dir_cli, dir_serv;
  struct ec obj;

	//verifica que a la hora de ejecutar, reciba como parametro la direccion 127.0.0.1
  if(argc != 2)
  {
		printf("Uso: %s <Direccion IP> \n", argv[0]);
		exit(1);
	}
  //--------------------------------------------------------------------------------
  	bzero( &dir_cli, sizeof(dir_cli));

  	if((sockfd = socket(AF_INET, SOCK_DGRAM,0))==-1)
		perror("Socket");

  	dir_cli.sin_family = AF_INET;
  	dir_cli.sin_addr.s_addr = INADDR_ANY;
  	dir_cli.sin_port = htons(PORT_UDP_CLI);

  	if(bind(sockfd,(struct sockaddr *)&dir_cli,sizeof(dir_cli))==-1)
		error("Cliente: no se puede asociar la direccion local");

  	bzero( &dir_serv,sizeof(dir_serv));

  	dir_serv.sin_family = AF_INET;
  	dir_serv.sin_addr.s_addr = inet_addr(argv[1]);
  	dir_serv.sin_port = htons(PORT_UDP_SERV);

    //Digite los siguientes datos
     printf("\ncoeficiente de x2 : ");
     scanf("%f",&obj.a);
     printf("\ncoeficiente de x1 : ");
     scanf("%f",&obj.b);
     printf("\nvalor de c : ");
     scanf("%f",&obj.c);

  	if(sendto(sockfd,&obj,sizeof(obj),0,(struct sockaddr *)&dir_serv,sizeof(dir_serv))==-1)
		error("Sendto");

  	n = recvfrom(sockfd,&obj,sizeof(obj),0,(struct sockaddr *)0,(int *)0);

  	if(n < 0)
    error("recvfrom");

		//Imprimiendo los datos
		printf("\nSolucion a la ecuacion: ");
		if(obj.imaginaria == 0 && obj.entera == 0){
	   		printf("\nvalor de x1 :%f\n",obj.x1);
	   		printf("valor de x2 :%f\n",obj.x2);
			}
	else{
	   		printf("\nx1 :%f + %fi \n",obj.entera,obj.imaginaria);
	   		printf("\nx2 :%f - %fi \n",obj.entera,obj.imaginaria);
	}
   	printf("\n");
   	exit(0);
}

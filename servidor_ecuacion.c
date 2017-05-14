#include "formula.h"

struct ec {
	float a,b,c,x1,x2,entera,imaginaria;
};

main(int argc, char *argv[1])
{
 		int sockfd,n,len_cli;
 		struct sockaddr_in dir_cli, dir_serv;
 		struct ec obj;
 		float raiz;

  	bzero((char*)&dir_serv,sizeof(dir_serv));

  	dir_serv.sin_family = AF_INET;
  	dir_serv.sin_addr.s_addr = htonl(INADDR_ANY);
  	dir_serv.sin_port = htons(PORT_UDP_SERV);

  	if((sockfd = socket(AF_INET,SOCK_DGRAM,0))<0)
		error("servidor: no se puede crear el socket");

  	if(bind(sockfd,(struct sockaddr *)&dir_serv,sizeof(dir_serv))<0)
		error("servidor: no se puede asociar la direccion local");

    for(;;){
    	len_cli = sizeof(dir_cli);
			n = recvfrom(sockfd,&obj,sizeof(obj),0,(struct sockaddr *)&dir_cli,&len_cli);
	    if(n<0)
			perror("servidor: recvfrom");
	    raiz=(obj.b*obj.b)-(4*obj.a*obj.c);
 			if(raiz<0)
	    {
	 				raiz=raiz*-1;
	 				raiz=sqrt(raiz);
	 				obj.imaginaria=raiz/(2*obj.a);
	 				obj.entera=(obj.b*-1)/(2*obj.a);
	 				obj.x1=0;
	 				obj.x2=0;
	 		}
	    else
			{
	 				raiz=sqrt(raiz);
	 				obj.imaginaria=0;
	 				obj.entera=0;
	 				obj.x1=((obj.b*-1)+raiz)/(2*obj.a);
	 				obj.x2=((obj.b*-1)-raiz)/(2*obj.a);
			}
			if(sendto(sockfd,&obj,sizeof(obj),0,(struct sockaddr *)&dir_cli,sizeof(dir_cli))==-1)
			error("servidor: sendto");
   }//fin de for
}

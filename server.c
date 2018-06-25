#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<netdb.h>
#include<unistd.h>
#include<stdlib.h>
void error(char *msg)
{
perror(msg);
exit(1);
}

int main(int argc, char *argv[])
{

int sockfd, newsockfd, portno, clilen;
//char buffer[1000];
struct sockaddr_in serv_addr, cli_addr;
int n;

if (argc < 2)
{
fprintf(stderr,"ERROR, no port provided\n");
exit(1);
}

sockfd = socket(AF_INET, SOCK_STREAM, 0);

if (sockfd < 0)
{
error("ERROR opening socket");
}

bzero((char *) &serv_addr, sizeof(serv_addr));

portno = atoi(argv[1]);

serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = INADDR_ANY;
serv_addr.sin_port = htons(portno);

if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
{
error("ERROR on binding");
}

listen(sockfd,5);

clilen = sizeof(cli_addr);

newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);

if (newsockfd < 0)
{
error("ERROR on accept");
}
printf("ADDRESS SERVER STARTED\n");
char xor2[9000];
int k;
char value[9000];
int d;
FILE *fp;
int i=0;

unsigned char xor[9000];
int j;
char key[9000];
char buf[9000];
char output[9000];
char buffer[9000];
//printf("ADDRESS SERVER STARTED\n");

bzero(buffer,9000);
while(n = read(newsockfd,buffer,9000)>0)
{
/**
int c;
for(c=0;c<strlen(buffer);c++)
printf("%02x ",buffer[c]);
**/

for(d=0;d<strlen(buffer);d++)
value[d]=buffer[d];
fp=fopen("mykey.txt","r");
if(fp!=NULL)
{
fread(buf,1,9000,fp);
buf[(sizeof buf)-1]=0;
strcpy(key,buf);
fclose(fp);
}
for(j=0;j<strlen(value);j++)
xor[j]=(char)(key[j]^value[j]);

/**
int a;   
for(a=0;a<strlen(xor);a++)
printf("%c",xor[a]);
**/
if(strcmp(xor,"harris@ics.uci.edu")==0)
strcpy(output,"Ian G. Harris");
else if(strcmp(xor,"tintuj@uci.edu")==0)
strcpy(output,"jose tintu");
else if(strcmp(xor,"joe@cnn.com")==0)
strcpy(output,"Joe Smith");
else if(strcmp(xor,"jane@slasdot.org")==0)
strcpy(output,"Jane Smith");
else if(strcmp(xor,"tintjose@gmail.com")==0)
strcpy(output,"tintu jose");
else
strcpy(output,"invalid email id");
if (n < 0)
{
error("ERROR reading from socket");
}

//printf("\nHere is the message: %s\n",output);
//char xor2[9000];
//int k;
for(k=0;k<strlen(output);k++)
xor2[k]=(char)(key[k]^output[k]);
n = write(newsockfd,xor2,strlen(xor2));
bzero(xor2,9000);//changed
bzero(buffer,9000);
bzero(xor,9000);
bzero(output,9000);
bzero(key,9000);
bzero(value,9000);
bzero(buf,9000);
}
if (n < 0)
{
error("ERROR writing to socket");
}
return 0;
}


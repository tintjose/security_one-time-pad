#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<netdb.h>
#include<stdlib.h>
#include<unistd.h>
void error(char *msg)
{
perror(msg);
exit(0);
}

int main(int argc, char *argv[])
{
int sockfd, portno, n;
struct sockaddr_in serv_addr;
struct hostent *server;
if (argc < 3)
{
fprintf(stderr,"usage %s hostname port\n", argv[0]);
exit(0);
}

portno = atoi(argv[2]);

sockfd = socket(AF_INET, SOCK_STREAM, 0);
if(sockfd<0)
{
error("ERROR opening socket");
}
server=gethostbyname(argv[1]);
if(server==NULL)
{
fprintf(stderr,"ERROR,no such host\n");
exit(0);
}

bzero((char *) &serv_addr,sizeof(serv_addr));
serv_addr.sin_family=AF_INET;

bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr,server->h_length);
serv_addr.sin_port = htons(portno);

if (connect(sockfd,&serv_addr,sizeof(serv_addr)) < 0)
{
error("ERROR connecting");
}
printf("ADDRESS SERVER STARTED");
FILE *fp;
int i;
char value[9000];
int c,j,b;
unsigned char xor[9000];
char buffer[9000];
char key[1000];
char buf[9000];
char xor1[9000];
int len;
char value1[9000];
char xor2[9000];
int e;
char ex[]="+++";
while(1)
{
fp=fopen("mykey.txt","r");
if(fp!=NULL)
{
fread(buf,1,9000,fp);
buf[(sizeof buf)-1]=0;
strcpy(key,buf);
fclose(fp);
}
printf("\nPlease enter email id: ");
bzero(buffer,9000);
fgets(buffer,9000,stdin);

for(c=0;c<strlen(buffer);c++)
value[c]=buffer[c];
if (strcmp(buffer,ex)==0)
{

return 0;
}
for(j=0;j<strlen(value);j++)
{xor[j]=(char)(key[j]^value[j]);
}
xor[j]='\0';
int a;
//for(a=0;a<strlen(xor);a++)
//printf("%02x ",xor[a]);
len=strlen(xor)-1;

for(b=0;b<len;b++)
xor1[b]=xor[b];
/**
for(a=0;a<strlen(xor1);a++)
printf("%02x ",xor1[a]);
**/
n = write(sockfd,xor1,strlen(xor1));
bzero(xor1,9000);
if (n < 0)
{
error("ERROR writing to socket");
}


bzero(buffer,9000);
n = read(sockfd,buffer,9000);

for(e=0;e<strlen(buffer);e++)
value1[e]=buffer[e];
for(j=0;j<strlen(value1);j++)
{xor2[j]=(char)(key[j]^value1[j]);
}

bzero(buf,9000);
bzero(xor1,9000);
bzero(value1,9000);
bzero(value,9000);
bzero(xor,9000);
bzero(key,9000);

if (n < 0)
{
error("ERROR reading from socket");
}
printf("%s\n",xor2);
bzero(xor2,9000);
}
return 0;
}

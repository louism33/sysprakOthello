#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>


//Die Prolog-Phase der Kommunikation 
char* mystrcat(char* str1, char* str2){
   int len1 = strlen(str1);
   int len2 = strlen(str2);
   char* newstr = malloc(128*sizeof(char));
   for(int i = 0; i < len1; i++){
        *(newstr + i) = *(str1 + i);
    }
   for(int j = 1; j <= len2; j++){
        *(newstr + len1 - 1 + j)=*(str2 + j - 1);
    }
return newstr;
}

char* createinfo(int idikator, char* daten){
  char temp1[] = "VERSION <<";
  char temp2[] = "Game-ID <<";
  char temp3[] = "PLAYER [[";
  char temp4[] = ">>";
  char temp5[] = "]]";
  char* version = &temp1[0];
  char* id = &temp2[0];
  char* player = &temp3[0];
  char* notation1 = &temp4[0];
  char* notation2 = &temp5[0];
  if(idikator == 1){
  char* msg = mystrcat(version, daten);
  char* version_msg = mystrcat(msg, notation1);
  return version_msg;}

  if(idikator == 2){
  char* msg = mystrcat(id, daten);
  char* id_msg = mystrcat(msg, notation1);
  return id_msg;}

  if(idikator == 3){
  char* player_msg = mystrcat(player, notation2);
  return player_msg;}
}


int performConnection(int sock, char* version, char* id){
    char* version_msg = createinfo(1, version);
    char* id_msg = createinfo(2, id);
    char* player_msg = createinfo(3, NULL);

    send(sock, version_msg, sizeof(version_msg)/sizeof(version_msg[0]), 0);
    send(sock, id_msg, sizeof(id_msg)/sizeof(id_msg[0]), 0);
    send(sock, player_msg, sizeof(player_msg)/sizeof(player_msg[0]), 0);
    
    printf("performConnection %d\n", sock);
}


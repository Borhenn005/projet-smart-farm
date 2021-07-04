#include <stdio.h>
#include <string.h>
#include "user.h"
void addUser(user u){
    FILE *f;
    f = fopen("../DataBase/user.txt","a");
    if(f != NULL){
        fprintf(f,"%s %s %d\n",u.username,u.password,u.role);
    }
    fclose(f);
    
}

int verif_user(char username[],char password[]){
    FILE *f;
    user u;
    f = fopen("../DataBase/user.txt","r");
    while(fscanf(f,"%s %s %d",u.username,u.password,&u.role) != EOF){
        if(strcmp(u.username,username) == 0){
            if(strcmp(u.password,password) == 0){
                return 1;
            }
        }
    }
    return 0;
}

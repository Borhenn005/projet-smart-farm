#ifndef __USER__H__
#define __USER__H__
typedef struct{

    char username[30];
    char password[30];
    int role;
    /*
        1 : Admin
        2 : Employer
    */
}user;
void addUser(user u);
int verif_user(char username[],char password[]);
#endif
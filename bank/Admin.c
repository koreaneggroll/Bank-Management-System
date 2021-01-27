#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//FUNCTION PROTOTYPES START
void set_password();
void get_users();
void menu();
void clearscreen();
//FUNCTION PROTOTYPES END


struct Admin{
  char username[15];
  char fname[15];
  char lname[15];
  int password;
  int age;
};


struct Admin admin = {"arincelmare", "Arin", "Grigoras", 123456, 12};


int main(void){
  menu();
}

//Prints out all the users
void get_users(){
  FILE *fptr;

  //char filename[100], c;
  char c;

  //printf("Enter the filename to open \n");
  //scanf("%s", filename);

  // Open file
  fptr = fopen("Accounts.txt", "r");

  if (fptr == NULL)
  {
      printf("Cannot open file \n");
      exit(0);
  }

  clearscreen();

  // Read contents from file
  c = fgetc(fptr);
  while (c != EOF)
  {
      printf ("%c", c);
      c = fgetc(fptr);
  }

  fclose(fptr);
}


//Sets the admins password
void set_password(){
  int pass;
  printf("\nSet password: ");
  scanf("%d", &pass);

  if(pass == admin.password){
    printf("\nNew password cannot be old password\n");
    menu();
  }

  admin.password = pass;
}




void menu(){
  int ch;
  do{
    printf("\n[1]. Change Password\n");
    printf("[2]. Get users\n");
    printf("Choice> ");

    scanf("%d", &ch);

    switch(ch){
      case 1:
        set_password();
        break;

      case 2:
        get_users();
        break;
    }
  }while(ch != 99);
}


//Clears screen
void clearscreen(){
  printf("\e[1;1H\e[2J");
}

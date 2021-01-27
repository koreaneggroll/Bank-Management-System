//INCLUDES START
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <time.h>
#include <string.h>
//INCLUDES END

#define BUFFER_SIZE 1000
//#define PASSWORD 1122334455

//FUNCTION PROTOTYPES START
void new_account();
void main_message();
int create_ID();
void account_history();
void store_accounts();
void clearscreen();
void replace();
void replaceAll();
void deposit();
void withdraw();
void menu();
void try_pass();
int get_age();
//FUNCTION PROTOTYPES END


struct Account{
  char username[15];
  char fname[15];
  char lname[15];
  int password;
  int acctype;
  int balance;
  int age;
  int id;
  struct date{
    int dd;
    int mm;
    int yyyy;
  }doj;
};


struct Account ac;



int main(void){
  menu();
}


void new_account(){
  //Main menu fucntion
  main_message();
  //Gets first name
  printf("\nFirst Name: ");
  scanf("%s", ac.fname);

  //gets the last Name
  printf("\nLast Name: ");
  scanf("%s", ac.lname);

  //gets username
  printf("\nUsername: ");
  scanf("%s", ac.username);

  //gets age
  printf("\nAge: ");
  scanf("%d", &ac.age);

  //Gets birth date
  printf("Enter birth date in dd/mm/yyyy format: ");
  scanf("%d/%d/%d", &ac.doj.dd, &ac.doj.mm, &ac.doj.yyyy);



  //check year
  if(ac.doj.yyyy>=1900 && ac.doj.yyyy<=9999)
  {
      //check month
      if(ac.doj.mm>=1 && ac.doj.mm<=12)
      {
          //check days
          if((ac.doj.dd>=1 && ac.doj.dd<=31) && (ac.doj.mm==1 || ac.doj.mm==3 || ac.doj.mm==5 || ac.doj.mm==7 || ac.doj.mm==8 || ac.doj.mm==10 || ac.doj.mm==12))
              printf("Date is valid.\n");
          else if((ac.doj.dd>=1 && ac.doj.dd<=30) && (ac.doj.dd==4 || ac.doj.dd==6 || ac.doj.dd==9 || ac.doj.dd==11))
              printf("Date is valid.\n");
          else if((ac.doj.dd>=1 && ac.doj.dd<=28) && (ac.doj.mm==2))
              printf("Date is valid.\n");
          else if(ac.doj.dd==29 && ac.doj.mm==2 && (ac.doj.yyyy%400==0 ||(ac.doj.yyyy%4==0 && ac.doj.yyyy%100!=0)))
              printf("Date is valid.\n");
          else
              printf("Day is invalid.\n");
      }
      else
      {
          printf("Month is not valid.\n");
      }
  }
  else
  {
      printf("Year is not valid.\n");
  }



  //Set ID
  ac.id = create_ID();
  printf("\nYour ID is: %d\n", ac.id);

  //gets account type
  printf("\nAccount type (1/0 for C/S): ");
  scanf("%d", &ac.acctype);

  //If account is Checking then set balance
  if(ac.acctype == 1){
    ac.balance = 1000;
  }
  //If account is Saving then set balance
  else if(ac.acctype == 0){
    ac.balance = 500;
  }
  else if(ac.acctype != 1 || ac.acctype != 0){
    printf("\nThat's not a valid ");
    exit(1);
  }

  //Sets password
  printf("\nLastly, please set your password: ");
  scanf("%d", &ac.password);

  //sleeps for 2 seconds
  sleep(2);

  printf("\nACCOUNT CREATED\n\n");

  //sleeps for 2 more seconds
  sleep(2);

  account_history();
  store_accounts();

}


//This function can edit only the names
void edit_account(){

  char *old_username = malloc(sizeof(char) * strlen(ac.username));
  strcpy(old_username, ac.username);

  clearscreen();

  printf("New Username: ");
  scanf("%s", ac.username);

  replace(old_username, ac.username);

  free(old_username);

}



//Function to deposit money
void deposit(){
  clearscreen();

  printf("\nCurrent balance: %d\n", ac.balance);

  int ammount; //the ammount they wawnt to deposit
  printf("\nHow much do you want to deposit? ");
  scanf("%d", &ammount);

  ac.balance += ammount;

  printf("\nNow your balance is: %d\n", ac.balance);

  FILE *fptr;
  //open the file
  fptr = fopen("Deposit_History.txt", "a");

  if(fptr == NULL){
    printf("\nCouldn't open the file\n");
  }

  fprintf(fptr, "%s deposited $%d", ac.username, ammount);
  fclose(fptr);
}



//Function to withdraw money
void withdraw(){
  char to[15]; //their email address
  int ammount; //the ammount they want to withdraw

  clearscreen();

  printf("\nCurrent balance: %d\n", ac.balance);

  printf("\nWho to withdraw to? (their email address): ");
  scanf("%s", to);
  printf("Ammount: ");
  scanf("%d", &ammount);

  ac.balance -= ammount;

  printf("\nYour balance now is: %d\n", ac.balance);

  FILE *fptr;
  fptr = fopen("Withdraw_history.txt", "a");

  if(fptr == NULL){
    printf("\nCouldn't open file\n");
    exit(1);
  }

  fprintf(fptr, "%s send $%d to %s\n", ac.username, ammount, to);

  fclose(fptr);
}



//Function to create a random ID everytime
int create_ID(){
  srand(time(NULL));
  int new_id = rand();

  return new_id;
}



//Function to write the last Account created
void account_history(){
  FILE *fptr;
  //open file
  fptr = fopen("account_history.txt", "a");

  if(fptr == NULL){
    printf("\nCouldn't open file\n");
    exit(1);
  }

  //write that the Account was created to a file
  fprintf(fptr, "Account %s was created\n", ac.username);
  fclose(fptr);
}



//Function to store the accounts
void store_accounts(){
  FILE *fptr;
  //opens the file
  fptr = fopen("Accounts.txt", "a");

  if(fptr == NULL){
    printf("\nCouldn't open file\n");
    exit(1);
  }

  fprintf(fptr, "Username: %s\n", ac.username);
  fprintf(fptr, "F_name: %s\n", ac.fname);
  fprintf(fptr, "L_name: %s\n", ac.lname);
  fprintf(fptr, "Age: %d\n", ac.age);
  fprintf(fptr, "Acc type: %d\n", ac.acctype);
  fprintf(fptr, "ID: %d\n", ac.id);
  fprintf(fptr, "\n");

  fclose(fptr);
}


void replace(char *oldWord, char *newWord){
  FILE * fPtr;
  FILE * fTemp;

  char buffer[BUFFER_SIZE];
  /*  Open all required files */
  fPtr  = fopen("Accounts.txt", "r");
  //fTemp = fopen("Replace.tmp", "w");

  /* fopen() return NULL if unable to open file in given mode. */
  if (fPtr == NULL)
  {
      /* Unable to open file hence exit */
      printf("\nUnable to open file.\n");
      printf("Please check whether file exists and you have read/write privilege.\n");
      exit(EXIT_SUCCESS);
  }


/*
 * Read line from source file and write to destination
 * file after replacing given word.
 */
 while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
 {
      // Replace all occurrence of word from current line
      replaceAll(buffer, oldWord, newWord);

      // After replacing write it to temp file.
      fputs(buffer, fTemp);
  }


  /* Close all files to release resource */
  fclose(fPtr);
  fclose(fTemp);


  /* delete original source file */
  //remove("Accounts.txt");

  /* Rename temp file as original file */
  //rename("replace.tmp", "Accounts.txt");

  printf("\nSuccessfully replaced all occurrences of '%s' with '%s'.", oldWord, newWord);
}

//Replaces all occurences of a word in a file
void replaceAll(char *str, const char *oldWord, const char *newWord)
{
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    int owlen;

    owlen = strlen(oldWord);


    /*
     * Repeat till all occurrences are replaced.
     */
    while ((pos = strstr(str, oldWord)) != NULL)
    {
        // Bakup current line
        strcpy(temp, str);

        // Index of current found word
        index = pos - str;

        // Terminate str after word found index
        str[index] = '\0';

        // Concatenate str with new word
        strcat(str, newWord);

        // Concatenate str with remaining words after
        // oldword found index.
        strcat(str, temp + index + owlen);
    }
}


//Reads the admins name
void get_admin_name(){
  FILE *fptr;

  //char filename[100], c;
  char c;

  //printf("Enter the filename to open \n");
  //scanf("%s", filename);

  // Open file
  fptr = fopen("Admin_name.txt", "r");

  if (fptr == NULL)
  {
      printf("Cannot open file \n");
      exit(0);
  }

  // Read contents from file
  c = fgetc(fptr);
  while (c != EOF)
  {
      printf ("%c", c);
      c = fgetc(fptr);
  }

  fclose(fptr);
}


//Reads all the admins data
void get_admin(){
  FILE *fptr;

  //char filename[100], c;
  char c;

  //printf("Enter the filename to open \n");
  //scanf("%s", filename);

  // Open file
  fptr = fopen("Admin.txt", "r");

  if (fptr == NULL)
  {
      printf("Cannot open file \n");
      exit(0);
  }

  // Read contents from file
  c = fgetc(fptr);
  while (c != EOF)
  {
      printf ("%c", c);
      c = fgetc(fptr);
  }

  fclose(fptr);
}


void menu(){
  int ch;

  do{
    printf("\n[1]. New Account\n");
    printf("[2]. Edit Account\n");
    printf("[3]. Get age\n");
    printf("[4]. Get ID\n");
    printf("[5]. Deposit\n");
    printf("[6]. Withdraw\n");
    printf("[7]. Show Admin's name\n");
    printf("[8]. Show All Admin's info\n");
    printf("[99]. EXIT\n");
    printf("Choice> ");

    scanf("%d", &ch);

    switch(ch){
      case 1:
        new_account();
        break;

      case 2:
        edit_account();
        break;

      case 3:
        printf("\n\n\nAGE: %d\n", get_age());
        break;

      case 4:
        printf("\n\n\nID: %d\n", get_id());
        break;

      case 5:
        deposit();
        break;

      case 6:
        withdraw();
        break;

      case 7:
        get_admin();
        break;

      case 8:
        get_admin();
        break;

    }

  }while(ch != 99);

}



//Function to display what the project is
void main_message(){
  printf("\nBANK MANAGEMENT SYSTEM\n");
}



//Clears screen
void clearscreen(){
  printf("\e[1;1H\e[2J");
}




//Password try
void try_pass(){
  int pass;

  while(pass != ac.password){
    printf("\nPassword: ");
    scanf("%d", &pass);
  }
}



//returns age
int get_age(){
  return ac.age;

  sleep(5);
}



//Returns ID
int get_id(){
  //Checks if the person knows the password to their account
  try_pass();

  return ac.id;

  sleep(5);
}

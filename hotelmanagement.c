#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>

void add(); 
void list();
void edit();
void delete1();
void search();

struct CustomerDetails {
    char roomnumber[10];
    char name[20];
    char address[25];
    char phonenumber[15];
    char nationality[15];
    char email[20];
    char days[10];
    char arrivaldate[10];
}s;

int main() {
    int i = 0;
    time_t t;
    time(&t);
    char choice;

user_login:
    printf("                                  WELCOME!!              \n\n");
    printf("\t\t*\n");
    printf("\t\t*                                           *\n");
    printf("\t\t*       ----------------------------        *\n");
    printf("\t\t*       #  HOTEL MANAGEMENT SYSTEM  #       *\n");
    printf("\t\t*       ----------------------------        *\n");
    printf("\t\t*                                           *\n");
    printf("\t\t*                                           *\n");
    printf("\t\t*                                           *\n");
    printf("\t\t*\n\n\n");

    for(i = 0; i < 80; i++)
        printf("-");
    printf("\nCurrent date and time : %s", ctime(&t));
    for(i = 0; i < 80; i++)
        printf("-");
    printf("\n");

    char username[15];
    char password[15];
    printf("\nEnter username: ");
    scanf("%s", username);
    printf("\nEnter password: ");
    scanf("%s", password);

    if(strcmp(username, "nithish") == 0) {
        if(strcmp(password, "nithish2112") == 0) {
            printf("Login successfully\n");
        } else {
            printf("Wrong password\n");
            getch();
            goto user_login;
        }
    } else {
        printf("User doesn't exist\n");
        getch();
        system("cls");
        goto user_login;
    }

    getch();
    while(1) {
        for(i = 0; i < 80; i++)
            printf("-");
        printf("\n");
        printf("   ******************************  |MAIN MENU|  ***************************** \n");
        for(i = 0; i < 80; i++)
            printf("-");
        printf("\n");
        printf("\t\t Please enter your choice for menu:\n\n");
        printf(" \n Enter 1 -> Book a room");
        printf("\n------------------------");
        printf(" \n Enter 2 -> View Customer Record");
        printf("\n----------------------------------");
        printf(" \n Enter 3 -> Delete Customer Record");
        printf("\n-----------------------------------");
        printf(" \n Enter 4 -> Search Customer Record");
        printf("\n-----------------------------------");
        printf(" \n Enter 5 -> Edit Record");
        printf("\n-----------------------");
        printf(" \n Enter 6 -> Exit");
        printf("\n-----------------");
        printf("\n");
        for(i = 0; i < 80; i++)
            printf("-");
        printf("\nCurrent date and time : %s", ctime(&t));
        for(i = 0; i < 80; i++)
            printf("-");
        
        choice = getche();
        //choice = toupper(choice);
        switch(choice) {
            case '1':
                add(); break;
            case '2':
                list(); break;
            case '3':
                delete1(); break;
            case '4':
                search(); break;
            case '5':
                edit(); break;
            case '6':
                printf("\n\n\t ****THANK YOU");
                printf("\n\t FOR TRUSTING OUR SERVICE");
                exit(0);
                break;
            default:
                printf("Incorrect Input");
                printf("\n Press any key to continue");
                getch();
        }
    }
}

void add() {
    FILE *f; 
    char test;
    f = fopen("add.txt", "a+");
    if(f == 0) {
        f = fopen("add.txt", "w+");
        system("cls");
        printf("Please hold on while we set our database in your computer!!");
        printf("\n Process completed press any key to continue!! ");
        getch();
    }
    while(1) {
        system("cls");
        printf("\n Enter Customer Details:\n");
        printf("\n Enter Room number: ");
        scanf("%s", s.roomnumber);
        fflush(stdin);
        printf("Enter Name: ");
        fgets(s.name, 20, stdin);
        printf("Enter Address: ");
        fgets(s.address, 25, stdin);
        printf("Enter Phone Number: ");
        scanf("%s", s.phonenumber);
        printf("Enter Nationality: ");
        scanf("%s", s.nationality);
        printf("Enter Email: ");
        scanf("%s", s.email);
        printf("Enter days (/x days): ");
        scanf("%s", s.days);
        printf("Enter Arrival date (dd/mm/yyyy): ");
        scanf("%s", s.arrivaldate);
        fwrite(&s, sizeof(s), 1, f);
        fflush(stdin);
        printf("\n\n1 Room is successfully booked!!");
        printf("\n Press esc key to exit, any other key to add another customer detail:");
        test = getche();
        if(test == 27)
            break;
    }
    fclose(f);
}

void list() {
    FILE *f;
    int i;
    if((f = fopen("add.txt", "r")) == NULL)
        exit(0);
    system("cls");

    printf("%-10s %-20s %-25s %-15s %-15s %-20s %-10s %-12s\n", 
           "ROOM", "NAME", "ADDRESS", "PHONENUMBER", 
           "NATIONALITY", "EMAIL", "DAYS", "ARRIVALDATE");

    for(i = 0; i < 127; i++)
        printf("-");
    printf("\n");

    while(fread(&s, sizeof(s), 1, f) == 1) {
        printf("%-10s %-20s %-25s %-15s %-15s %-20s %-10s %-12s\n", 
               s.roomnumber, s.name, s.address, s.phonenumber, 
               s.nationality, s.email, s.days, s.arrivaldate);
    }

    printf("\n");
    for(i = 0; i < 127; i++)
        printf("-");
    printf("\n");

    fclose(f);
    getch();
}


void delete1() {
    FILE *f, *t;
    int i = 1;
    char roomnumber[20];
    if((t = fopen("temp.txt", "w")) == NULL)
        exit(0);
    if((f = fopen("add.txt", "r")) == NULL)
        exit(0);
    system("cls");
    printf("Enter the Room Number of the hotel to be deleted from the database: \n");
    fflush(stdin);
    scanf("%s", roomnumber);
    while(fread(&s, sizeof(s), 1, f) == 1) {
        if(strcmp(s.roomnumber, roomnumber) == 0) {
            i = 0;
            continue;
        } else {
            fwrite(&s, sizeof(s), 1, t);
        }
    }
    if(i == 1) {
        printf("\n\n Records of Customer in this Room number is not found!!");
        getch();
        fclose(f);
        fclose(t);
        main();
    }
    fclose(f);
    fclose(t);
    remove("add.txt");
    rename("temp.txt", "add.txt");
    printf("\n\nThe Customer is successfully removed....");
    getch();
}

void search() {
    FILE *f;
    char roomnumber[20];
    int flag = 1;
    f = fopen("add.txt", "r+");
    if(f == 0)
        exit(0);
    fflush(stdin);
    printf("\nEnter Room number of the customer to search its details: \n");
    scanf("%s", roomnumber);
    while(fread(&s, sizeof(s), 1, f) == 1) {
        if(strcmp(s.roomnumber, roomnumber) == 0) {
            flag = 0;
            printf("\n\tRecord Found\n ");
            printf("\nRoom Number:\t%s", s.roomnumber);
            printf("\nName:\t%s", s.name);
            printf("\nAddress:\t%s", s.address);
            printf("\nPhone number:\t%s", s.phonenumber);
            printf("\nNationality:\t%s", s.nationality);
            printf("\nEmail:\t%s", s.email);
            printf("\nDays:\t%s", s.days);
            printf("\nArrival date:\t%s", s.arrivaldate);
            flag = 0;
            break;
        }
    }
    if(flag == 1) {
        printf("\n\tRequested Customer could not be found!");
    }
    getch();
    fclose(f);
}

void edit() {
    FILE *f;
    int k = 1;
    char roomnumber[20];
    long int size = sizeof(s);
    if((f = fopen("add.txt", "r+")) == NULL)
        exit(0);
    system("cls");
    printf("Enter Room number of the customer to edit:\n\n");
    scanf("%s", roomnumber);
    fflush(stdin);
    while(fread(&s, sizeof(s), 1, f) == 1) {
        if(strcmp(s.roomnumber, roomnumber) == 0) {
            k = 0;
            printf("\nEnter Room Number: ");
            scanf("%s", s.roomnumber);
            printf("\nEnter Name: ");
            scanf("%s", s.name);
            printf("\nEnter Address: ");
            scanf("%s", s.address);
            printf("\nEnter Phone Number: ");
            scanf("%s", s.phonenumber);
            printf("\nEnter Nationality: ");
            scanf("%s", s.nationality);
            printf("\nEnter Email: ");
            scanf("%s", s.email);
            printf("\nEnter Days: ");
            scanf("%s", s.days);
            printf("\nEnter Arrival Date: ");
            scanf("%s", s.arrivaldate);
            fseek(f, -size, SEEK_CUR);
            fwrite(&s, sizeof(s), 1, f);
            break;
        }
    }
    if(k == 1) {
        printf("\n\nTHE RECORD DOESN'T EXIST!!!!");
        fclose(f);
        getch();
    } else {
        fclose(f);
        printf("\n\n\t\tYOUR RECORD IS SUCCESSFULLY EDITED!!!");
        getch();
    }
}


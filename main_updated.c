//******************************************************************************************************/
//<<<--------------------------------------- TEAM LAMBDA ------------------------------------------->>>//

//                                             Authors                                                 //
//-------------------------------------------------------+---------------------------------------------//
//                         NAME                          +             G# NUMBER                       //
//-------------------------------------------------------+---------------------------------------------//
//          Ramaswamy Iyappan                            -             G01348097                       //
//          Sai Ramya Kadali                             -             G01351874                       //
//          Lakshmi Chetana Gomaram Bikshapathireddy     -             G01353352                       //
//          Sai Sucharitha Ginjupalli                    -             G01328384                       //
//-------------------------------------------------------+---------------------------------------------//

//                              Date        :   May 3, 2022                                            //
//                              Subject     :   This file is the main() file for assignment-3          //
//                              program     :   main.c                                                 //

//******************************************************************************************************/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<mysql.h>
#include"mylibrary.h"

int main()
{
    char sql_query[100],user_query[50];
    MYSQL *conn = mysql_init(NULL);
    char user[20];
    char password[30];
    char sql_statement[2048];

    if (mysql_real_connect(conn, "helios.vse.gmu.edu", "riyappan", "ygredose", "riyappan", 0, NULL, 0) == NULL)
        show_error(conn);

    if(mysql_query(conn,"TRUNCATE TABLE CART"))   // Emptying cart each time when the program runs, to treat each run as a new user.
        show_error(conn);

    int choice;
    start:
    do                  // runs recursively till any error or when the user wishes to exit.
    {
        system("clear");
        printf("\n\t\t\t\t\t\t\t\t\t     +----------------- MAIN MENU -----------------+      ");
        printf("\n\t\t\t\t\t\t\t\t\t     |                                             |      ");
        printf("\n\t\t\t\t\t\t\t\t\t     |       [1.]       Admin                      |      ");
        printf("\n\t\t\t\t\t\t\t\t\t     |       [2.]       Search for Products        |      ");
        printf("\n\t\t\t\t\t\t\t\t\t     |       [3.]       My Shopping Cart           |      ");
        printf("\n\t\t\t\t\t\t\t\t\t     |       [4.]       Quit                       |      ");
        printf("\n\t\t\t\t\t\t\t\t\t     |                                             |      ");
        printf("\n\t\t\t\t\t\t\t\t\t     +---------------------------------------------+      ");
        printf("\n\n\t\t\t\t\t\t\t\t     Enter an option: ");
        if(scanf("%d",&choice)==1)
        {
            int f=getchar();
            if(f==0)
            printf(" ");
        }
        switch(choice)
        {
            case 1:                 // Admin Module
            {
                admin(conn);
                break;
            }
            case 2:                 // Search Module
            {
                search(conn);
                getchar();
                break;
            }
            case 3:                 // Shopping Cart Module
            {
                int flag=0;
                run_again:
                system("clear");
                flag = cart(conn);
                if (flag == 0)
                    goto run_again;
                break;
            }
            case 4:                 // to quit
            {   printf("\nProgram Exited...\n");
                exit(0);
                break;
            }
            default:
            {
                printf("\n\t\t\t\t\t\t\t\t    Invalid Choice..");
                printf("\n\t\t\t\t\t\t\t\t    Please enter any valid choice(only from the available options)");
                printf("\n\t\t\t\t\t\t\t\t                                  [OR]                             ");
                printf("\n\t\t\t\t\t\t\t\t    Press 4 if you want to exit! ");
                getchar();
                goto start;
                break;
            }
        }
    }while(choice>=1 && choice<=4);
	mysql_close(conn);
	exit(0);
}
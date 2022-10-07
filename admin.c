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
//                              Subject     :   This file is the admin Module for assignment-3         //
//                              program     :   admin.c                                                //

//******************************************************************************************************/



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<mysql.h>
#include<ctype.h>
#include"mylibrary.h"

//Function to perform all operations of the ADMIN Module
// Purpose: To implement the admin functionalities
// Functionalities: admin credentials validation, insertion, deletion, display, return to main menu

void admin(MYSQL *conn)
{
    char admin_password[20];
    try_again:

    printf("\n\t\t\t\t\t\t\t\t     Enter Password to login as Admin : ");
    scanf("%s",&admin_password);

    if (strcmp("AVENGERS_ASSEMBLE",admin_password)==0)              // Given it as a sample password to check for authorization.
    {                                                               // Without entering this, won't go inside the ADMIN function.
        printf("\n\t\t\t\t\t\t\t\t     One moment please...\n"); sleep(1);  //Change it if required.
        printf("  \t\t\t\t\t\t\t\t                      . .\n"); sleep(1);
        printf("  \t\t\t\t\t\t\t\t                       . \n"); sleep(1);

        admin:
        system("clear");
        sleep(0.8);
        int ch;
        printf("\n\t\t\t\t\t\t\t\t\t        Sub Menu - ADMIN                    \n");
        sleep(0.8);
        printf("\n\t\t\t\t\t\t\t\t\t    1. Insert Product Info                    ");
        printf("\n\t\t\t\t\t\t\t\t\t    2. Delete Product Info                    ");
        printf("\n\t\t\t\t\t\t\t\t\t    3. Display the list of Products           ");
        printf("\n\t\t\t\t\t\t\t\t\t    4. Return to Main Menu                    ");
        printf("\n\n\t\t\t\t\t\t\tHello BOSS!.                          ");
        sleep(0.8);
        printf("\n\n\t\t\t\t\t\t\tEnter any option: ");
        if(scanf("%d",&ch)==1)
        {
            int f=getchar();
            if(f==0)
            printf(" ");
        }
        // Switch case to handle the 'INSERT', 'DELETE', 'DISPLAY' and 'RETURN TO MAIN MENU' options.
        switch(ch)
        {
            case 1:                     // Calls function insert() for inserting records into existing product tables.
            {
                system("clear");
                if (mysql_query(conn,"SELECT * FROM PRODUCTS"))
                    show_error(conn);
                display_products(conn);
                insert_info(conn);
                printf("\n\nEnter any key to go back.. ");
                getchar();
                goto admin;
                break;
            }
            case 2:                     // Case to delete either an entire product table or a particular item.
            {
                int disp_choice;
                printf("\n\t\t\t\t\t\t\t   -> 1. Delete Product                 ");
                printf("\n\t\t\t\t\t\t\t   -> 2. Delete Product Item            ");
                printf("\n\t\t\t\t\t\t\t   -> 3. Return to Sub Menu             ");
                printf("\n\n\t\t\t\t\t\t\tEnter any option: ");
                scanf("%d",&disp_choice);
                getchar();
                switch(disp_choice)
                {
                    case 1:
                    {
                        system("clear");
                        char product_name[20],my_query[50],del_query[50],del_name[20];
                        if (mysql_query(conn,"SELECT * FROM PRODUCTS"))
                            show_error(conn);
                        display_products(conn);

                        printf("\nEnter the product to be deleted : ");
                        scanf("%s",&product_name);
                        getchar();
                        strcpy(del_name,product_name);
                        sprintf(my_query,"DROP TABLE %s", product_name);
                        if (mysql_query(conn,my_query))
                        {
                            show_error(conn);
                        }

                        sprintf(del_query,"DELETE FROM PRODUCTS WHERE PRODUCT_NAME = '%s'", del_name);
                        if (mysql_query(conn,del_query))
                        {
                            show_error(conn);
                        }

                        printf("\nProduct %s was successfully deleted from the database..!",product_name);
                        getchar();
                        break;
                    }
                    case 2:
                    {
                        label2:
                        system("clear");
                        char product_name[20],my_query[50],delete_item[10],new_query[50];
                        //printf("\nProducts available are..\n");
                        if (mysql_query(conn,"SELECT * FROM PRODUCTS"))
                            show_error(conn);
                        display_products(conn);

                        printf("\nSelect the product to delete items from : ");
                        scanf("%s",&product_name);
                        printf("\n");

                        for(int i=0; product_name[i]; i++)
                            product_name[i] = tolower(product_name[i]);

                        if((strcmp(product_name,"camera")==0) || (strcmp(product_name,"laptop")==0) || (strcmp(product_name,"speaker")==0) || (strcmp(product_name,"watch")==0) || (strcmp(product_name,"mobile_phones")==0) || (strcmp(product_name,"microwave")==0) || (strcmp(product_name,"washing_machine")==0) || (strcmp(product_name,"refrigerators")==0))
                        {

                            draw_lines(product_name);
                            display_columns(conn,product_name);
                            draw_lines(product_name);

                            sprintf(my_query,"SELECT * FROM %s",product_name);
                            if (mysql_query(conn,my_query))
                                show_error(conn);
                            display(conn);
                            draw_lines(product_name);

                            printf("\nEnter the product ID of the item to be deleted: ");
                            scanf("%s",&delete_item);
                            sprintf(new_query,"DELETE FROM %s where PRODUCT_ID = '%s'",product_name,delete_item);
                            if (mysql_query(conn,new_query))
                                show_error(conn);
                            printf("\nItem %s was Successfully deleted from %s ..",delete_item,product_name);
                            getchar();
                            break;
                        }
                        else
                        {
                            printf("\nKindly enter a valid input..");
                            getchar();
                            goto label2;
                        }
                    }
                    case 3:
                    {
                        goto admin;
                        break;
                    }
                }
                printf("\nEnter any key to go back.. ");
                getchar();
                goto admin;
                break;
            }
            case 3:
            {
                int display_choice;
                printf("\n\t\t\t\t\t\t\t   -> 1. Display number of products         ");
                printf("\n\t\t\t\t\t\t\t   -> 2. Display Product details           	");
                printf("\n\t\t\t\t\t\t\t   -> 3. Return to Sub Menu                 ");
                printf("\n\n\t\t\t\t\t\t\tEnter any option: ");
                scanf(" %d",&display_choice);
                getchar();
                switch(display_choice)
                {
                    case 1:
                    {
                        label:
                        system("clear");
                        if (mysql_query(conn,"SELECT * FROM PRODUCTS"))
                            show_error(conn);
                        display_products(conn);

                        char disp_query[50],disp_name[20];
                        printf("\nEnter Product Name to display items for : ");
                        scanf("%s",&disp_name);
                        getchar();

                        for(int i=0; disp_name[i]; i++)
                            disp_name[i] = tolower(disp_name[i]);

                        if((strcmp(disp_name,"camera")==0) || (strcmp(disp_name,"laptop")==0) || (strcmp(disp_name,"speaker")==0) || (strcmp(disp_name,"watch")==0) || (strcmp(disp_name,"mobile_phones")==0) || (strcmp(disp_name,"microwave")==0) || (strcmp(disp_name,"washing_machine")==0) || (strcmp(disp_name,"refrigerators")==0))
                        {

                            sprintf(disp_query,"SELECT BRAND,SUM(PIECES_AVAILABLE) FROM %s GROUP BY BRAND",disp_name);
                            printf("\n\t\t\t\t\t\t\t\t\t\t<<|-Printing Number of items in Stock-|>>  \n");
                            printf("\t\t\t\t\t\t\t\t\t        +---------------------------------------+  \n");

                            if (mysql_query(conn, disp_query))
                                show_error(conn);

            	            MYSQL_RES *result = mysql_store_result(conn);
                            if (result==NULL)
                                show_error(conn);
                            int num_fields = mysql_num_fields(result);
                            MYSQL_ROW row;
                            while ((row=mysql_fetch_row(result)))
                            {
                                printf("\t\t\t\t\t\t\t\t\t        ");
                                for(int i=0; i<num_fields; i++)
                                {
                                    printf("|");
                                    printf("  %-14s   ",row[i]);
                                }
                                printf("|\n");
                            }
                            mysql_free_result(result);

                            printf("\t\t\t\t\t\t\t\t\t        +---------------------------------------+  \n\n");
                            //display(conn);
                            printf("\nEnter any key to go back.. ");
                            getchar();
                            goto admin;
                            break;
                        }
                        else
                        {
                            printf("\nKindly enter a valid input..");
                            getchar();
                            goto label;
                        }
                    }
                    case 2:
                    {
                        label1:
                        system("clear");
                        if (mysql_query(conn,"SELECT * FROM PRODUCTS"))
                            show_error(conn);
                        display_products(conn);

                        char user_query[50],sql_query[50];
                        memset(user_query,0,sizeof(user_query));
                        printf("Enter Product Name to display items for : ");
                        scanf("%s",&user_query);
                        getchar();

                        for(int i=0; user_query[i]; i++)
                            user_query[i] = tolower(user_query[i]);

                        if((strcmp(user_query,"camera")==0) || (strcmp(user_query,"laptop")==0) || (strcmp(user_query,"speaker")==0) || (strcmp(user_query,"watch")==0) || (strcmp(user_query,"mobile_phones")==0) || (strcmp(user_query,"microwave")==0) || (strcmp(user_query,"washing_machine")==0) || (strcmp(user_query,"refrigerators")==0))
                        {
                            printf("\n\t\t\t\t\t\t\t\t\t\t    | || Printing items in Stock || |  \n\n");

                            draw_lines(user_query);
                            display_columns(conn,user_query);
                            draw_lines(user_query);

                            sprintf(sql_query,"SELECT * FROM %s",user_query);
                            if (mysql_query(conn, sql_query))
                                show_error(conn);
                            display(conn);
                            draw_lines(user_query);

                            printf("\nEnter any key to go back.. ");
                            getchar();
                            goto admin;
                            break;
                        }
                        else
                        {
                            printf("\nKindly enter a valid input..");
                            getchar();
                            goto label1;
                        }
                    }
                    case 3:
                    {
                        goto admin;
                        break;
                    }
                }
                break;
            }
            case 4:
            {
                break;
            }
        }
    }
    else
    {
        printf("\n\t\t\t\t\t\t\t\t     Wrong Password !! Try again..");
        goto try_again;
    }
}
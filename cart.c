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
//                              Subject     :   This file is the Cart Module for assignment-3          //
//                              program     :   cart.c                                                 //

//******************************************************************************************************/



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<mysql.h>
#include<ctype.h>
#include"mylibrary.h"

// Purpose: To implement the shopping cart functionalities including adding items to cart,
// displaying items added and returning to the menu
int cart(MYSQL *conn)
{
    int ch;
    cart_lable:
    system("clear");
    printf("\n\t\t\t\t\t\t\t\t\t\t         Sub Menu - SHOPPING CART                    \n");
    printf("\n\t\t\t\t\t\t\t\t\t\t          1. Add items to Cart                        ");
    printf("\n\t\t\t\t\t\t\t\t\t\t          2. Display current Cart                     ");
    printf("\n\t\t\t\t\t\t\t\t\t\t          3. Return to Main Menu                      ");
    printf("\n\n\t\t\t\t\t\t\tEnter any option: ");  //user option
    if(scanf("%d",&ch)==1)
    {
        int f=getchar();
        if(f==0)
            printf(" ");
    }
    switch(ch)
    {
        case 1: //adding items to cart
        {
            add:
            system("clear");
            if (mysql_query(conn,"SELECT * FROM PRODUCTS"))
                show_error(conn);
            display_products(conn);

            int flag=0,quantity;
            char prod_name[20],shop_query[100],prod_id[15],id[10],buy,some_id[15];
            memset(some_id,0,sizeof(some_id));
            memset(prod_id,0,sizeof(prod_id));

            printf("\n\nEnter the Product you want to buy : ");
            scanf("%s",&prod_name);
            getchar();

            for(int i=0; prod_name[i]; i++)
                prod_name[i] = tolower(prod_name[i]);

            if((strcmp(prod_name,"camera")==0) || (strcmp(prod_name,"laptop")==0) || (strcmp(prod_name,"speaker")==0) || (strcmp(prod_name,"watch")==0) || (strcmp(prod_name,"mobile_phones")==0) || (strcmp(prod_name,"microwave")==0) || (strcmp(prod_name,"washing_machine")==0) || (strcmp(prod_name,"refrigerators")==0))
            {

                draw_lines(prod_name);

                display_columns(conn,prod_name);
                draw_lines(prod_name);

                sprintf(shop_query,"SELECT * FROM %s",prod_name);
                if(mysql_query(conn,shop_query))
                    show_error(conn);
                display(conn);

                draw_lines(prod_name);

                printf("\n\nEnter Product ID of the item you want to buy: ");
                scanf("%s",&prod_id);
                getchar();
                printf("\nEnter Number of pieces: ");
                scanf("%d",&quantity);
                getchar();
                printf("\nDo you want to add %d %s(s) to the cart ? [Y/N] :", quantity, prod_name);
                scanf("%s",&buy);
                getchar();
                strcpy(some_id,prod_id);

                if(buy=='Y' || buy=='y')
                {
                    char add_query[100],modify_query[50],update_price[50],yes_or_no;
                    sprintf(add_query,"INSERT INTO CART SELECT PRODUCT_ID,BRAND,PRICE_IN_DOLLARS,PIECES_AVAILABLE FROM %s WHERE PRODUCT_ID = '%s' ",prod_name,some_id);
                    if(mysql_query(conn,add_query))
                        show_error(conn);

                    sprintf(modify_query,"UPDATE CART SET QUANTITY = %d WHERE PRODUCT_ID = '%s' ",quantity,some_id);
                    if(mysql_query(conn,modify_query))
                        show_error(conn);

                    sprintf(update_price,"UPDATE CART SET PRICE_IN_DOLLARS = (PRICE_IN_DOLLARS * %d) WHERE PRODUCT_ID = '%s' ",quantity,some_id);
                    if(mysql_query(conn,update_price))
                        show_error(conn);

                    printf("\nItem added to cart Successfully..!\n");
                    printf("Press enter to view..\n");
                    getchar();

                    system("clear");
                    if(mysql_query(conn,"SELECT * FROM CART"))
                        show_error(conn);
                    display_cart(conn);

                    if(mysql_query(conn,"SELECT SUM(PRICE_IN_DOLLARS) FROM CART"))
                        show_error(conn);
                    printf("\n\t\t\t\t\t\t\t\tTotal Price[$] : ");
                    display_total(conn,"tot");

                    printf("\n\t\t\t\t\t\t\t\tSales Tax : 6%% ");
                    printf("\n\t\t\t\t\t\t\t\tTotal Amount to be paid : ");

                    if(mysql_query(conn,"SELECT SUM(PRICE_IN_DOLLARS)*1.06 FROM CART"))
                        show_error(conn);
                    display_total(conn,"tax");

                    printf("\nDo you want to add more items? [Y/N] :");
                    scanf("%c",&yes_or_no);
                    getchar();
                    if(yes_or_no=='N' || yes_or_no=='n')
                        flag=1;
                    if(yes_or_no=='Y' || yes_or_no=='y')
                        goto add;
                }
                else
                    flag=1;

                if (flag == 0)
                    return flag;

                char check,update_query[50];
                printf("\nProceed to checkout ? [Y/N] : ");
                scanf("%c",&check);
                getchar();
                if(check=='Y' || check=='y')
                {
                    char random[15];
                    strcpy(random,some_id);
                    sprintf(update_query,"UPDATE %s SET PIECES_AVAILABLE = PIECES_AVAILABLE-%d WHERE (PRODUCT_ID = '%s')",prod_name,quantity,random);
                    if(mysql_query(conn,update_query))
                        show_error(conn);

                    Write_to_file(conn);
                    if(mysql_query(conn,"TRUNCATE TABLE CART"))
                        show_error(conn);

                    printf("\t\t\t\t\t\t\t\t\t\t\t     Bill Generated..!!");
                    printf("\n\n\t\t\t\t\t\t\t\t\t      Thank you for shopping with us. Have a good day!\n");
                    mysql_close(conn);
                    exit(0);
                }
                else
                {
                    goto cart_lable;
                }
                return flag;
                break;
            }
            else
            {
                printf("\nKindly enter a valid input..");
                getchar();
                goto add;
            }
        }
        case 2:  //display
        {
            int choice;
            system("clear");
            if(mysql_query(conn,"SELECT * FROM CART"))
                show_error(conn);

            MYSQL_RES *result_cart = mysql_store_result(conn);
            MYSQL_ROW row_cart = mysql_fetch_row(result_cart);
            if(!row_cart)
            {
                printf("\n\n\n\t\t\t\t\t\t\t\t\t\t         Your Cart is Empty				\n");
                printf("\n\t\t\t\t\t\t\t\t\t\t       Enter any key..");
                getchar();
                goto cart_lable;
                break;
            }
            mysql_free_result(result_cart);

            if(mysql_query(conn,"SELECT * FROM CART"))
                show_error(conn);
            display_cart(conn);

            if(mysql_query(conn,"SELECT SUM(PRICE_IN_DOLLARS) FROM CART"))
                show_error(conn);
            printf("\n\t\t\t\t\t\t\t\tTotal Price : ");
            display_total(conn,"tot");

            printf("\n\t\t\t\t\t\t\t\tSales Tax : 6%% ");
            printf("\n\t\t\t\t\t\t\t\tTotal Amount to be paid : ");

            if(mysql_query(conn,"SELECT SUM(PRICE_IN_DOLLARS)*1.06 FROM CART"))
                show_error(conn);
            display_total(conn,"tax");

            printf("\n\n\t\t\t\t\t\t\t\t\t\t         What you want to do? \n");
            printf("\n\t\t\t\t\t\t\t\t\t\t       1. Proceed to checkout ");
            printf("\n\t\t\t\t\t\t\t\t\t\t       2. Remove all items from Cart");
            printf("\n\t\t\t\t\t\t\t\t\t\t       3. Return back ");
            printf("\n\n\t\t\t\t\t\t\tEnter an option: ");
            if(scanf("%d",&choice)==1)
            {
                int f=getchar();
                if(f==0)
                    printf(" ");
            }
            switch (choice)
            {
                case 1:
                {
                    Write_to_file(conn);
                    if(mysql_query(conn,"TRUNCATE TABLE CART"))
                        show_error(conn);

                    printf("\t\t\t\t\t\t\t\t\t\t\t     Bill Generated..!!");
                    printf("\n\n\t\t\t\t\t\t\t\t\t      Thank you for shopping with us. Have a good day!\n");
                    mysql_close(conn);
                    exit(0);
                    break;
                }
                case 2:
                {
                    if(mysql_query(conn,"TRUNCATE TABLE CART"))
                        show_error(conn);
                    printf("\n\t\t\t\t\t\t\t\t\t\t       The cart has been emptied.");
                    printf("\n\t\t\t\t\t\t\t\t\t\t       Enter any key..");
                    getchar();
                    goto cart_lable;
                    break;
                }
                case 3:
                {
                    goto cart_lable;
                    break;
                }
            }
        }
        case 3:
        {
            break;
        }
    }
}
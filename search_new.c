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
//                              Subject     :   This file is to search for existing products           //
//                              program     :   search_new.c                                           //

//******************************************************************************************************/



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<mysql.h>
#include<ctype.h>
#include"mylibrary.h"

//Function to search for existing products in the database and search based on user's criteria.
void search(MYSQL *conn)
{
    char tablenm[25],brand[25],range,order[5],model[25],color[10];
    char query1[100],query2[150],query3[50],query[50];
    label:
    system("clear");
    sleep(1);
    printf("\n\t\t\t\t\t\t\t\t\t\t         Sub Menu - Search                    \n");
    if (mysql_query(conn,"SELECT * FROM PRODUCTS"))
        show_error(conn);
    display_products(conn);

    printf("\n\nSelect any product you want to search for : ");
    scanf("%s",&tablenm);
    getchar();

    for(int i=0; tablenm[i]; i++)
        tablenm[i] = tolower(tablenm[i]);

    //if not found in existing products
    if((strcmp(tablenm,"camera")==0) || (strcmp(tablenm,"laptop")==0) || (strcmp(tablenm,"speaker")==0) || (strcmp(tablenm,"watch")==0) || (strcmp(tablenm,"mobile_phones")==0) || (strcmp(tablenm,"microwave")==0) || (strcmp(tablenm,"washing_machine")==0) || (strcmp(tablenm,"refrigerators")==0))
    {
        printf("\nBrands available in %s are\n",tablenm);
        sprintf(query1,"SELECT DISTINCT BRAND FROM %s",tablenm);
        if (mysql_query(conn,query1))
            show_error(conn);
        printf("\n+--------------------+\n");
        display(conn);
        printf("+--------------------+\n");

        printf("\nSelect any Brand you want : ");
        scanf("%s",&brand);
        getchar();

        if((strcmp(tablenm,"camera")==0) || (strcmp(tablenm,"laptop")==0) || (strcmp(tablenm,"speaker")==0) || (strcmp(tablenm,"mobile_phones")==0))
        //camera laptop mobile_phone speaker
        {
            printf("\nModels available in %s are\n",brand);
            sprintf(query,"SELECT DISTINCT MODEL FROM %s WHERE BRAND='%s'",tablenm,brand);
            if (mysql_query(conn,query))
                show_error(conn);
            printf("\n+--------------------+\n");
            display(conn);
            printf("+--------------------+\n");

            printf("\nSelect any Model you want : ");
            scanf("%s",&model);
            getchar();
        }
        else
        {
            printf("\nColors available in %s are\n",brand);
            sprintf(query,"SELECT DISTINCT COLOR FROM %s WHERE BRAND='%s'",tablenm,brand);
            if (mysql_query(conn,query))
                show_error(conn);
            printf("\n+--------------------+\n");
            display(conn);
            printf("+--------------------+\n");

            printf("\nEnter any color you want : ");
            scanf("%s",&color);
            getchar();
        }

        printf("\nEnter order of price range [L for Low-High / H for High-Low] : ");
        scanf("%c",&range);
        getchar();

        system("clear");
        sleep(1);
        printf("\n\n\t\t\t\t\t\t\t    <---------- Displaying product details based on the entered search criteria ---------->\n\n");

        draw_lines(tablenm);
        display_columns(conn,tablenm);
        draw_lines(tablenm);

        if(range=='H' || range=='h') // descending order
            sprintf(query2,"SELECT * FROM %s ORDER BY PRICE_IN_DOLLARS DESC",tablenm);
        else    // ascending order
            sprintf(query2,"SELECT * FROM %s ORDER BY PRICE_IN_DOLLARS ASC",tablenm);

        if (mysql_query(conn,query2))
            show_error(conn);
        //printf("\t");

	    MYSQL_RES *result = mysql_store_result(conn);
        if (result==NULL)
            show_error(conn);

        int num_fields = mysql_num_fields(result);
        MYSQL_ROW row;

        while ((row=mysql_fetch_row(result)))
        {
            if ( strcmp(row[1],brand)==0 || strcmp(row[2],model)==0 || strcmp(row[2],color)==0 || strcmp(row[3],color)==0 || strcmp(row[4],color)==0 )
            //printf("\t");
                for(int i=0; i<num_fields; i++)
                {
                    printf("|");
                    printf(" %-17s ",row[i]);
                }
            else
                continue;
            printf(" |\n");
        }
        mysql_free_result(result);

        //printf("\t");
        draw_lines(tablenm);

        printf("\nEnter any key to go back to the main screen.. ");
        return;
    }
    else
    {
        printf("\nKindly enter a valid input..");
        getchar();
        goto label;
    }
}
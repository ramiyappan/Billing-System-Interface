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
//                              Subject     :   This file is the display module for all functions      //
//                              program     :   display.c                                              //

//******************************************************************************************************/



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<mysql.h>
#include"mylibrary.h"

//Function for displaying fields in a Table
void display(MYSQL *conn)
{
	MYSQL_RES *result = mysql_store_result(conn);
	if (result==NULL)
		show_error(conn);

    int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;

	while ((row=mysql_fetch_row(result)))
	{
        for(int i=0; i<num_fields; i++)
		{
			printf("|");
			printf(" %-17s ",row[i]);
		}
	printf("|\n");
	}
	mysql_free_result(result);
}

//Function for displaying the product table
void display_products(MYSQL *conn)
{
	MYSQL_RES *result = mysql_store_result(conn);
	if (result==NULL)
		show_error(conn);

    int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;

    printf("\n\t\t\t\t\t\t\t\t\t          <<----- PRODUCTS AVAILABLE ----->>");
    printf("\n\t\t\t\t\t\t\t\t\t\t  |--------------------------------|");
    int no=1;
    while ((row=mysql_fetch_row(result)))
	{
        for(int i=0; i<num_fields; i++)
		{
			printf("\n\t\t\t\t\t\t\t\t\t\t  |       %d.  %-16s     |",no++,row[i]);
		}
	}
	printf("\n\t\t\t\t\t\t\t\t\t\t  |--------------------------------|");
    printf("\n\t\t\t\t\t\t\t\t\t\t  +--------------------------------+");
    printf("\n");
	mysql_free_result(result);
}

//function to display the cart table
void display_cart(MYSQL *conn)
{
	MYSQL_RES *result = mysql_store_result(conn);
	if (result==NULL)
		show_error(conn);

    int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;

    printf("\n\t\t\t\t\t\t\t\t<<---------------------------- Items in Cart ---------------------------->>");
	printf("\n\t\t\t\t\t\t\t\t+    PRODUCT ID   |      BRAND      |      PRICE      |     QUANTITY      +");
    printf("\n\t\t\t\t\t\t\t\t|-------------------------------------------------------------------------|\n");
    int no=1;
    while ((row=mysql_fetch_row(result)))
	{
		printf("\t\t\t\t\t\t\t\t");
        for(int i=0; i<num_fields; i++)
		{
			printf("|      %-10s ",row[i]);
		}
		printf("  |\n");
	}
	printf("\t\t\t\t\t\t\t\t|-------------------------------------------------------------------------|\n");
    printf("\t\t\t\t\t\t\t\t+-------------------------------------------------------------------------+");
    printf("\n");
	mysql_free_result(result);
}

//function to display the total price
void display_total(MYSQL *conn, char tot[])
{
	MYSQL_RES *result = mysql_store_result(conn);
    if (result==NULL)
        show_error(conn);
    MYSQL_ROW row;
	float num;
	row=mysql_fetch_row(result);
	if (strcmp(tot,"tot")==0)
		printf("$%s",row[0]);
	else
	{
		num = atof(row[0]);
		printf("$%.2f",num);
	}
	mysql_free_result(result);
}

//functio to display column names of all tables
void display_columns(MYSQL *conn,char prod_name[])
{
	char column_query[50];
	sprintf(column_query,"DESCRIBE %s",prod_name);
    if(mysql_query(conn,column_query))
        show_error(conn);

	MYSQL_RES *result = mysql_store_result(conn);
	if (result==NULL)
		show_error(conn);

    int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;

	while((row=mysql_fetch_row(result)))
	{
		printf("|");
		printf(" %-17s ",row[0]);
	}
	printf("|\n");
	mysql_free_result(result);
}

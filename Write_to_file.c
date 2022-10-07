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
//                              Subject     :   This file is to write the bill to a text file          //
//                              program     :   Write_to_file.c                                        //

//******************************************************************************************************/



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<mysql.h>
#include"mylibrary.h"

// Function to Write contents of CART table to a file, showcasing it in a bill format when the user wishes to checkout.
void Write_to_file(MYSQL *conn)
{
    FILE *fptr;
    fptr = fopen("BILL.txt","w");
    if(fptr==NULL)
    {
        printf("\nError in opening file");
        exit(1);
    }

    if(mysql_query(conn,"SELECT * FROM CART"))              // Writing the CART table in BILL.txt when checking out.
        show_error(conn);

    MYSQL_RES *result = mysql_store_result(conn);
	if (result==NULL)
		show_error(conn);

    int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;

    fprintf(fptr,"\n\n\t\t\t\t\t\t\t\t\t\t\t      BILL RECEIPT    ");
    fprintf(fptr,"\n\t\t\t\t\t\t\t\t\t\t\t  <------------------>    \n");
    fprintf(fptr,"\n\t\t\t\t\t\t\t\t+-------------------------------------------------------------------------+");
    fprintf(fptr,"\n\t\t\t\t\t\t\t\t|    PRODUCT ID   |      BRAND      |      PRICE      |     QUANTITY      |");
    fprintf(fptr,"\n\t\t\t\t\t\t\t\t+-------------------------------------------------------------------------+\n");

    while ((row=mysql_fetch_row(result)))
	{
        fprintf(fptr,"\t\t\t\t\t\t\t\t");

        for(int i=0; i<num_fields; i++)
			fprintf(fptr,"|      %-10s ",row[i]);
        fprintf(fptr,"  |\n");
	}
    mysql_free_result(result);

    fprintf(fptr,"\t\t\t\t\t\t\t\t+-------------------------------------------------------------------------+\n");

    if(mysql_query(conn,"SELECT SUM(PRICE_IN_DOLLARS) FROM CART"))      // Printing sum(price) of all items
        show_error(conn);

    result = mysql_store_result(conn);
    if (result==NULL)
        show_error(conn);

    num_fields = mysql_num_fields(result);
    row=mysql_fetch_row(result);
    fprintf(fptr,"\n\n\t\t\t\t\t\t\t\tTotal Price :  $%s  ",row[0]);
    mysql_free_result(result);

    fprintf(fptr,"\n\t\t\t\t\t\t\t\tSales Tax : 6%% ");

    if(mysql_query(conn,"SELECT SUM(PRICE_IN_DOLLARS)*1.06 FROM CART"))     // Adding 6% sales tax to the bill
        show_error(conn);

    result = mysql_store_result(conn);
    if (result==NULL)
        show_error(conn);

    float num;
    row=mysql_fetch_row(result);
    num = atof(row[0]);
    fprintf(fptr,"\n\t\t\t\t\t\t\t\tTotal Amount to be paid :  $%.2f  ",num);
    fprintf(fptr,"\n");
    mysql_free_result(result);

    fprintf(fptr,"\n\n\t\t\t\t\t\t\t\t\t      Thank you for shopping with us. Have a good day!\n");
    fclose(fptr);
}

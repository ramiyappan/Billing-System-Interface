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
//                              Subject     :   This file is the insert function for assignment-3      //
//                              program     :   insert.c                                               //

//******************************************************************************************************/



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<mysql.h>
#include"mylibrary.h"

//Function to insert new records into existing product tables in the database.
void insert_info(MYSQL *conn)
{
    int table_option;
    char char_atr1[50],char_atr2[50],char_atr3[50],char_atr4[50],char_atr5[50],char_atr6[50],char_atr7[50];
    int int_atr,pieces;
    float price,float_atr;
    char use_query[100];

    printf("\nChoose an option to add items under a product : ");
    if(scanf("%d",&table_option)==1)
    {
        int f=getchar();
        if(f==0)
        printf(" ");
    }
    if (table_option>=1 && table_option<=8) //Will enter only for these options
    {
        switch(table_option)
        {
            case 1: //Camera
            {
                printf("\nEnter Camera details..\n");
                printf("\nProduct ID: ");                   scanf("%s",&char_atr1);
                printf("\nBrand: ");                        scanf("%s",&char_atr2);
                printf("\nModel: ");                        scanf("%s",&char_atr3);
                printf("\nPixel in MP: ");                  scanf("%s",&char_atr4);
                printf("\nMemory in GB: ");                 scanf("%s",&char_atr5);
                printf("\nPrice: ");                        scanf("%f",&price);
                printf("\nPieces: ");                       scanf("%d",&pieces);
                sprintf(use_query,"INSERT INTO camera VALUES ('%s','%s','%s','%s','%s',%f,%d)",
                char_atr1,char_atr2,char_atr3,char_atr4,char_atr5,price,pieces);
                if(mysql_query(conn,use_query))
                    show_error(conn);
                printf("\nAdded item successfully..");
                getchar();
                break;
            }
            case 2: //Laptop
            {
                printf("\nEnter Laptop details..\n");
                printf("\nProduct ID: ");                   scanf("%s",&char_atr1);
                printf("\nBrand: ");                        scanf("%s",&char_atr2);
                printf("\nModel: ");                        scanf("%s",&char_atr3);
                printf("\nOperating System: ");             scanf("%s",&char_atr4);
                printf("\nMemory: ");                       scanf("%s",&char_atr5);
                printf("\nRAM: ");                          scanf("%s",&char_atr6);
                printf("\nProduct Condition [New/Used]: "); scanf("%s",&char_atr7);
                printf("\nPrice: ");                        scanf("%f",&price);
                printf("\nPieces: ");                       scanf("%d",&pieces);
                sprintf(use_query,"INSERT INTO laptop VALUES ('%s','%s','%s','%s','%s','%s','%s',%f,%d)",
                char_atr1,char_atr2,char_atr3,char_atr4,char_atr5,char_atr6,char_atr7,price,pieces);
                if(mysql_query(conn,use_query))
                    show_error(conn);
                printf("\nAdded item successfully..");
                getchar();
                break;
            }
            case 3: //Microwave
            {
                printf("\nEnter Microwave details..\n");
                printf("\nProduct ID: ");                   scanf("%s",&char_atr1);
                printf("\nBrand: ");                        scanf("%s",&char_atr2);
                printf("\nColor: ");                        scanf("%s",&char_atr3);
                printf("\nMaterial: ");                     scanf("%d",&int_atr);
                printf("\nWeight [Pounds]: ");              scanf("%f",&float_atr);
                printf("\nCapacity [Cubic Meters]: ");       scanf("%s",&char_atr4);
                printf("\nPrice: ");                        scanf("%f",&price);
                printf("\nPieces: ");                       scanf("%d",&pieces);
                sprintf(use_query,"INSERT INTO microwave VALUES ('%s','%s','%s',%d,%f,'%s',%f,%d)",
                char_atr1,char_atr2,char_atr3,int_atr,float_atr,char_atr4,price,pieces);
                if(mysql_query(conn,use_query))
                    show_error(conn);
                printf("\nAdded item successfully..");
                getchar();
                break;
            }
            case 4: //Mobile_phones
            {
                printf("\nEnter Mobile phone details..\n");
                printf("\nProduct ID: ");                   scanf("%s",&char_atr1);
                printf("\nBrand: ");                        scanf("%s",&char_atr2);
                printf("\nModel: ");                        scanf("%s",&char_atr3);
                printf("\nCamera: ");                       scanf("%s",&char_atr4);
                printf("\nMemory: ");                       scanf("%s",&char_atr5);
                printf("\nRAM: ");                          scanf("%s",&char_atr6);
                printf("\nProduct Condition [New/Used]: "); scanf("%s",&char_atr7);
                printf("\nPrice: ");                        scanf("%f",&price);
                printf("\nPieces: ");                       scanf("%d",&pieces);
                sprintf(use_query,"INSERT INTO mobile_phones VALUES ('%s','%s','%s','%s','%s','%s','%s',%f,%d)",
                char_atr1,char_atr2,char_atr3,char_atr4,char_atr5,char_atr6,char_atr7,price,pieces);
                if(mysql_query(conn,use_query))
                    show_error(conn);
                printf("\nAdded item successfully..");
                getchar();
                break;
            }
            case 5: //refrigerators
            {
                printf("\nEnter Refrigerator details..\n");
                printf("\nProduct ID: ");                   scanf("%s",&char_atr1);
                printf("\nBrand: ");                        scanf("%s",&char_atr2);
                printf("\nCapacity[Cubic Feet]: ");         scanf("%f",&float_atr);
                printf("\nNumber of Doors: ");              scanf("%d",&int_atr);
                printf("\nColor: ");                        scanf("%s",&char_atr3);
                printf("\nPrice: ");                        scanf("%f",&price);
                printf("\nPieces: ");                       scanf("%d",&pieces);
                sprintf(use_query,"INSERT INTO refrigerators VALUES ('%s','%s',%f,%d,'%s',%f,%d)",
                char_atr1,char_atr2,float_atr,int_atr,char_atr3,price,pieces);
                if(mysql_query(conn,use_query))
                    show_error(conn);
                printf("\nAdded item successfully..");
                getchar();
                break;
            }
            case 6: //speaker
            {
                printf("\nEnter Speaker details..\n");
                printf("\nProduct ID: ");                   scanf("%s",&char_atr1);
                printf("\nBrand: ");                        scanf("%s",&char_atr2);
                printf("\nModel: ");                        scanf("%s",&char_atr3);
                printf("\nBattery Life: ");                 scanf("%s",&char_atr4);
                printf("\nColor: ");                        scanf("%s",&char_atr5);
                printf("\nWater Resistant [YES/NO]: ");     scanf("%s",&char_atr6);
                printf("\nPrice: ");                        scanf("%f",&price);
                printf("\nPieces: ");                       scanf("%d",&pieces);
                sprintf(use_query,"INSERT INTO speaker VALUES ('%s','%s','%s','%s','%s',%s',%f,%d)",
                char_atr1,char_atr2,char_atr3,char_atr4,char_atr5,char_atr6,price,pieces);
                if(mysql_query(conn,use_query))
                    show_error(conn);
                printf("\nAdded item successfully..");
                getchar();
                break;
            }
            case 7: //Washing_machine
            {
                printf("\nEnter Washing Machine details..\n");
                printf("\nProduct ID: ");                   scanf("%s",&char_atr1);
                printf("\nBrand: ");                        scanf("%s",&char_atr2);
                printf("\nAccess Location[Top/Front]: ");   scanf("%s",&char_atr3);
                printf("\nColor: ");                        scanf("%s",&char_atr4);
                printf("\nCapacity: ");                     scanf("%s",&char_atr5);
                printf("\nMAX Spin Speed: ");               scanf("%d",&int_atr);
                printf("\nPrice: ");                        scanf("%f",&price);
                printf("\nPieces: ");                       scanf("%d",&pieces);
                sprintf(use_query,"INSERT INTO washing_machine VALUES ('%s','%s','%s','%s','%s',%d,%f,%d)",
                char_atr1,char_atr2,char_atr3,char_atr4,char_atr5,int_atr,price,pieces);
                if(mysql_query(conn,use_query))
                    show_error(conn);
                printf("\nAdded item successfully..");
                getchar();
                break;
            }
            case 8: //Watch
            {
                printf("\nEnter Watch details..\n");
                printf("\nProduct ID: ");                   scanf("%s",&char_atr1);
                printf("\nBrand: ");                        scanf("%s",&char_atr2);
                printf("\nColor: ");                        scanf("%s",&char_atr3);
                printf("\nSmart Watch [YES/NO]: ");         scanf("%s",&char_atr4);
                printf("\nGPS [YES/NO]: ");                 scanf("%s",&char_atr5);
                printf("\nBluetooth [YES/NO]: ");           scanf("%s",&char_atr6);
                printf("\nWarranty [Years]: ");             scanf("%d",&int_atr);
                printf("\nPrice: ");                        scanf("%f",&price);
                printf("\nPieces: ");                       scanf("%d",&pieces);
                sprintf(use_query,"INSERT INTO watch VALUES ('%s','%s','%s','%s','%s','%s',%d,%f,%d)",
                char_atr1,char_atr2,char_atr3,char_atr4,char_atr5,char_atr6,int_atr,price,pieces);
                if(mysql_query(conn,use_query))
                    show_error(conn);
                printf("\nAdded item successfully..");
                getchar();
                break;
            }
        }
    }
    else
    {
        printf("\nKindly enter a valid input..");    //reprompting the user
        getchar();
        return;
    }
}
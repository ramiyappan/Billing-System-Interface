#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<mysql.h>
#include"mylibrary.h"

static char *host = "helios.vse.gmu.edu";
static char *user = "riyappan";
static char *pass = "ygredose";
static char *dbname = "riyappan";

/* void show_error();
void display();
void delete_table();
void insert_info();
void Write_to_file();
extern int cart();
*/


void Write_to_file(MYSQL *conn)
{
    FILE *fptr;
    fptr = fopen("BILL.txt","w");
    if(fptr==NULL)
    {
        printf("\nError in opening file");
        exit(1);
    }
    if(mysql_query(conn,"SELECT * FROM CART"))
        show_error(conn);

    MYSQL_RES *result = mysql_store_result(conn);
	if (result==NULL)
		show_error(conn);

    int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;

    fprintf(fptr,"\n\n\t\t\t\t\t\t\t\t\t\t\t      BILL RECEIPT    ");
    fprintf(fptr,"\n\t\t\t\t\t\t\t\t\t\t\t  <------------------>    \n\n");
    while ((row=mysql_fetch_row(result)))
	{
        fprintf(fptr,"\t\t\t\t\t\t\t");
        for(int i=0; i<num_fields; i++)
			fprintf(fptr,"   %-12s  ",row[i]);
	fprintf(fptr,"\n");
	}
    mysql_free_result(result);


    if(mysql_query(conn,"SELECT SUM(PRICE_IN_DOLLARS) FROM CART"))
        show_error(conn);

    result = mysql_store_result(conn);
    if (result==NULL)
        show_error(conn);

    num_fields = mysql_num_fields(result);

    while ((row=mysql_fetch_row(result)))
    {
        for(int i=0; i<num_fields; i++)
            fprintf(fptr,"\n\t\t\t\t\t\t\t   TOTAL :  $%s  ",row[i]);
    fprintf(fptr,"\n");
    }
    mysql_free_result(result);

    fprintf(fptr,"\n\n\t\t\t\t\t\t\t\t\t      Thank you for shopping with us. Have a good day!\n");
    fclose(fptr);
}

 int cart(MYSQL *conn)
{
    int flag=0,quantity;
    char prod_name[20],shop_query[100],prod_id[15],id[10],buy,some_id[15];
    memset(some_id,0,sizeof(some_id));
    memset(prod_id,0,sizeof(prod_id));

    printf("\n\nEnter the Product you want to buy : ");
    scanf("%s",&prod_name);
    getchar();
    sprintf(shop_query,"SELECT * FROM %s",prod_name);
    if(mysql_query(conn,shop_query))
        show_error(conn);
    display(conn);

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

        printf("Item added to cart Successfully..!\n");
        printf("\n\t\t<-- Items in Cart -->\n");

        if(mysql_query(conn,"SELECT * FROM CART"))
            show_error(conn);
        display(conn);

        if(mysql_query(conn,"SELECT SUM(PRICE_IN_DOLLARS) FROM CART"))
            show_error(conn);
        printf("\nTotal[$] : ");
        display(conn);

        printf("\nDo you want to add more items? [Y/N] :");
        scanf("%c",&yes_or_no);
        getchar();
        if(yes_or_no=='N' || yes_or_no=='n')
            flag=1;
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
        if(mysql_query(conn,"TRUNCATE TABLE CART"))
            show_error(conn);
        printf("\n\n\t\t\t\t\t\t\t\t\t\t  Thank you for visiting..!!\n");
        mysql_close(conn);
        exit(0);
    }
    return flag;
}



void insert_info(MYSQL *conn)
{
    int table_option;
    char char_atr1[50],char_atr2[50],char_atr3[50],char_atr4[50],char_atr5[50],char_atr6[50],char_atr7[50],char_atr8[50];
    int int_atr,pieces;
    float price,float_atr;
    char use_query[100];

    printf("\nChoose an option to add items under a product : ");
    scanf("%d",&table_option);
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
            printf("\nProcessor: ");                    scanf("%s",&char_atr4);
            printf("\nOperating System: ");             scanf("%s",&char_atr5);
            printf("\nMemory: ");                       scanf("%s",&char_atr6);
            printf("\nRAM: ");                          scanf("%s",&char_atr7);
            printf("\nProduct Condition [New/Used]: "); scanf("%s",&char_atr8);
            printf("\nPrice: ");                        scanf("%f",&price);
            printf("\nPieces: ");                       scanf("%d",&pieces);
            sprintf(use_query,"INSERT INTO laptop VALUES ('%s','%s','%s','%s','%s','%s','%s','%s',%f,%d)",
            char_atr1,char_atr2,char_atr3,char_atr4,char_atr5,char_atr6,char_atr7,char_atr8,price,pieces);
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
            printf("\nCapacity [Cubic Meters: ");       scanf("%s",&char_atr4);
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
            printf("\nOperating System: ");             scanf("%s",&char_atr5);
            printf("\nMemory: ");                       scanf("%s",&char_atr6);
            printf("\nRAM: ");                          scanf("%s",&char_atr7);
            printf("\nProduct Condition [New/Used]: "); scanf("%s",&char_atr8);
            printf("\nPrice: ");                        scanf("%f",&price);
            printf("\nPieces: ");                       scanf("%d",&pieces);
            sprintf(use_query,"INSERT INTO mobile_phones VALUES ('%s','%s','%s','%s','%s','%s','%s','%s',%f,%d)",
            char_atr1,char_atr2,char_atr3,char_atr4,char_atr5,char_atr6,char_atr7,char_atr8,price,pieces);
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


void display(MYSQL *conn)
{
	MYSQL_RES *result = mysql_store_result(conn);
	if (result==NULL)
		show_error(conn);

    int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;

    //printf("\n");
    while ((row=mysql_fetch_row(result)))
	{
        for(int i=0; i<num_fields; i++)
			printf("   %-15s  ",row[i]);
	printf("\n");
	}
    printf("\n");
	mysql_free_result(result);
}

void display_products(MYSQL *conn)
{
	MYSQL_RES *result = mysql_store_result(conn);
	if (result==NULL)
		show_error(conn);

    int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;

    printf("\n\t\t\t\t\t\t\t\t\t\t    <<----- PRODUCTS AVAILABLE ----->>\n");
    int no=1;
    while ((row=mysql_fetch_row(result)))
	{
        for(int i=0; i<num_fields; i++)
			printf("\n\t\t\t\t\t\t\t\t\t\t\t    %d. %s",no++,row[i]);
	}
    printf("\n");
	mysql_free_result(result);
}



//Function to display error
void show_error(MYSQL *conn)
{
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    exit(1);
}

int main()
{
    char sql_query[100],user_query[50];
    MYSQL *conn = mysql_init(NULL);
    char user[20];
    char password[30];
    char sql_statement[2048];

    if (mysql_real_connect(conn, "helios.vse.gmu.edu", "riyappan", "ygredose", "riyappan", 0, NULL, 0) == NULL)
        show_error(conn);

    int choice;
    start:
    do
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
            case 1:
            {
                char admin_password[20];
                try_again:

                printf("\n\t\t\t\t\t\t\t\t     Enter Password to login as Admin : ");
                scanf("%s",&admin_password);

                if (strcmp("AVENGERS_ASSEMBLE",admin_password)==0)
                {
                    printf("\n\t\t\t\t\t\t\t\t     One moment please...\n"); sleep(1);
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
                    switch(ch)
                    {
                        case 1:
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
                        case 2:
                        {
                            int disp_choice;
                            printf("\n\t\t\t\t\t\t\t   -> 1. Delete Product                 ");
                            printf("\n\t\t\t\t\t\t\t   -> 2. Delete Product Item            ");
                            printf("\n\t\t\t\t\t\t\t   -> 3. Return to Sub Menu             ");
                            printf("\n\n\t\t\t\t\t\t\tEnter any option: ");
                            scanf("%d",&disp_choice);
                            switch(disp_choice)
                            {
                                case 1:
                                {
                                    system("clear");
                                    char product_name[20],my_query[50];
                                    if (mysql_query(conn,"SELECT * FROM PRODUCTS"))
                                        show_error(conn);
                                    display_products(conn);

                                    printf("\nEnter the product to be deleted : ");
                                    scanf("%s",&product_name);
                                    sprintf(my_query,"DROP TABLE %s", product_name);
                                    if (mysql_query(conn,my_query))
                                    {
                                        show_error(conn);
                                    }
                                    printf("\nProduct %s was successfully deleted from the database..!",product_name);
                                    getchar();
                                    break;
                                }
                                case 2:
                                {
                                    system("clear");
                                    char product_name[20],my_query[50],delete_item[10],new_query[50];
                                    //printf("\nProducts available are..\n");
                                    if (mysql_query(conn,"SELECT * FROM PRODUCTS"))
                                        show_error(conn);
                                    display_products(conn);

                                    printf("\nSelect the product to delete items from : ");
                                    scanf("%s",&product_name);
                                    printf("\n");
                                    sprintf(my_query,"SELECT * FROM %s",product_name);
                                    if (mysql_query(conn,my_query))
                                        show_error(conn);
                                    display(conn);

                                    printf("\nEnter the product ID of the item to be deleted: ");
                                    scanf("%s",&delete_item);
                                    sprintf(new_query,"DELETE FROM %s where PRODUCT_ID = '%s'",product_name,delete_item);
                                    if (mysql_query(conn,new_query))
                                        show_error(conn);
                                    printf("\nItem %s was Successfully deleted from %s ..",delete_item,product_name);
                                    getchar();
                                    break;
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
                            scanf("%d",&display_choice);
                            switch(display_choice)
                            {
                                case 1:
                                {
                                    if (mysql_query(conn,"SELECT * FROM PRODUCTS"));
                                        show_error(conn);
                                    display_products(conn);
                                    break;
                                }
                                case 2:
                                {
                                    system("clear");
                                    if (mysql_query(conn,"SELECT * FROM PRODUCTS"))
                                        show_error(conn);
                                    display_products(conn);

                                    char user_query[50],sql_query[50];
                                    memset(user_query,0,sizeof(user_query));
                                    printf("Enter Product Name to display items for : ");
                                    scanf("%s",&user_query);
                                    getchar();

                                    sprintf(sql_query,"SELECT * FROM %s",user_query);
                                    printf("\n\t\t\t\t\t\t\t\t\t\t    | || Printing items in Stock || |  \n\n");

                                    if (mysql_query(conn, sql_query))
                                        show_error(conn);
                                    display(conn);
                                    printf("\n\t\tEnter any key to go back.. ");
                                    getchar();
                                    goto admin;
                                    break;
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
                    printf("\nWrong Password !! Try again..");
                    goto try_again;
                }
                //admin(conn);
                break;
            }
            case 2:
            {
                system("clear");
                sleep(1);
                printf("\t\t        Sub Menu - Search                         \n");
                printf("\n Searchable Items:                                    ");
                printf("\n 1. Laptop    2. Phone    3. Fridge                   ");
                printf("\n\nSelect any item: ");
                getchar();
                system("clear");
                sleep(1);
                printf("\t      Search -> Searching for Laptop..              \n");
                sleep(2);
                printf("\n\t  Brand : {}                Condition : {}          ");
                printf("\n\t  Operating System : {}     Processor : {}          ");
                printf("\n\nSort by atr5 [High/Low] : ");
                getchar();
                printf("\n\n    ----------- Displaying Search Results --------- ");
                printf("\nEnter any key to go back to the main screen.. ");
                //search(conn);
                getchar();
                break;
            }
            case 3:
            {
                int flag=0;
                run_again:
                system("clear");
                printf("\n\t\t\t\t\t\t\t\t\t\t         Sub Menu - SHOPPING CART                    \n");
                if (mysql_query(conn,"SELECT * FROM PRODUCTS"))
                    show_error(conn);
                display_products(conn);

                flag = cart(conn);
                if (flag == 0)
                    goto run_again;

                getchar();
                break;
            }
            case 4:
            {   printf("\nProgram Exited...\n");
                exit(0);
                break;
            }
            default:
            {
                system("clear");
                printf("\nInvalid Choice..");
                printf("\nPlease enter any valid choice(only from the available options)");
                printf("\n                              [OR]                             ");
                printf("\nPress 8 if you want to exit!: ");
                goto start;
                break;
            }
        }
    }while(choice>=1 && choice<=4);
	mysql_close(conn);
	exit(0);
}
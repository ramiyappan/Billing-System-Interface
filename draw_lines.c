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
//                              Subject     :   This file is for drawing lines to show as tables       //
//                              program     :   main.c                                                 //

//******************************************************************************************************/



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<mysql.h>
#include"mylibrary.h"


//Function to draw lines based on the size of a table
void draw_lines(char product_name[])
{
	if(strcmp(product_name,"speaker")==0 || strcmp(product_name,"washing_machine")==0 || strcmp(product_name,"microwave")==0)
	{
		printf("+");
		for(int j=0;j<159;j++) //printing lines for 8 attributes
			if( j==19 || j==39 || j==59 || j==79 || j== 99 || j==119 || j==139)
				printf("+");
			else
				printf("-");
		printf("+\n");
	}

	if(strcmp(product_name,"mobile_phones")==0 || strcmp(product_name,"laptop")==0 || strcmp(product_name,"watch")==0)
	{
		printf("+");
		for(int j=0;j<179;j++) //printing lines
			if( j==19 || j==39 || j==59 || j==79 || j== 99 || j==119 || j==139 || j==159)
				printf("+");
			else
				printf("-");
		printf("+\n");
	}

	if(strcmp(product_name,"refrigerators")==0 || strcmp(product_name,"camera")==0)
	{
		printf("+");
		for(int j=0;j<139;j++) //printing lines
			if( j==19 || j==39 || j==59 || j==79 || j== 99 || j==119 )
				printf("+");
			else
				printf("-");
		printf("+\n");
	}
}

/*
*****************************************************************************

  File        : main.cpp

  The MIT License (MIT)
  Copyright (c) 2018 STMicroelectronics

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

*****************************************************************************
*/

#include "../core/public.h"

struct Box
{
		bool is_mine;
		bool is_checked;
		char value;
};

struct Box M_box[8][8];


bool restart;
bool is_first_step;

void display()
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<7;j++)
		{
			if(M_box[i][j].is_checked==FALSE)
			{
				printf("_|");
				fflush(stdout);
			}
			else
			{
				printf("%c|",M_box[i][j].value);
				fflush(stdout);
			}
		}
		if(M_box[i][7].is_checked==FALSE)
		{
			puts("_");
		}
		else
		{
			printf("%c\n",M_box[i][7].value);
			fflush(stdout);
		}
	}
}

void setup()
{
	restart=FALSE;
	is_first_step=TRUE;
	display();
}

int count_mine(int x,int y)
{
	int count=0;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(x-1+i>=0 && x-1+i<8 && y-1+j>=0 && y-1+j<8)
			{
				if(M_box[x-1+i][y-1+j].is_mine==TRUE)
				{
					count++;
				}
			}
		}
	}

	return count;
}

void build_map()
{
	for(int i=0;i<10;i++)
	{
		int row,col;
		row=rand()%8;
		col=rand()%8;
		if(M_box[row][col].is_mine==FALSE && M_box[row][col].is_checked==FALSE)
		{
			M_box[row][col].value='*';
			M_box[row][col].is_mine=TRUE;
		}
		else
		{
			i--;
		}
	}
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(M_box[i][j].is_mine==FALSE)
			{
				M_box[i][j].value='0'+count_mine(i,j);
			}
		}
	}
}

void refresh(int x,int y)
{
	if(M_box[x][y].is_mine==TRUE)
	{
		puts("BOOM! Better luck the next time!");

	}
	else if(M_box[x][y].value==0)
	{
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				M_box[x-1+i][y-1+j].is_checked=TRUE;
			}
		}
	}
	else
	{
		M_box[x][y].is_checked=TRUE;
	}
}



void sweep()
{
	int a,b;
	scanf("%i %i",&a,&b);

	M_box[a][b].is_checked=TRUE;
	if(is_first_step==TRUE)
	{
		build_map(a,b);
		refresh(a,b);
		is_first_step=FALSE;
	}
	else
	{
		refresh(a,b);
	}
	display();
}

int main(void){

	setup();
	while(restart==FALSE)
	{
		sweep();

	}


	return 0;
}

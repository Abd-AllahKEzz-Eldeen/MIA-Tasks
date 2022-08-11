#include <iostream>
#include <windows.h>
using namespace std;
void gotoxy(int x,int y)            // function to determine the coordinates we are going to write there
{
    COORD coord={0,0};
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
int main()
{
    for(int i=0;i<5;i++)            // drawing the regular columns of stars
    {
         gotoxy(0,0+i);
         cout<<"*    *    *";
    }

    for(int i=0; i<5;i++)

        for(int j=0;j<5;j++)
    {
        if((i==1)||(i==3))break;

        else if(i==0)                       // drawing the top layer of I letter
        {
            gotoxy(8+j,0);
            cout<<"*";
        }

        else if(i==2)                       // drawing the middle of H letter
        {
            gotoxy(0+j,2);
            cout << "*";
        }

        else if(i==4)                       // drawing the bottom of I letter
        {
            gotoxy(8+j,4);
            cout<<"*";
        }
    }
}



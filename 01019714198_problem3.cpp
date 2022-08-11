#include <iostream>
using namespace std;
#include <string.h>
int main()
{
    int q;

    char s[30][1000],o[30][1000];               // the string array which has the encrypted message and the output array

    cin>>q;                                     // receiving the number of test cases

    fflush(stdin);

    for(int i =0; i<q;i++)
    {

        int k=0;

        gets(s[i]);

        for(int j=0;j<strlen(s[i]);j++)
            {

                if(s[i][j+2]=='&')                  // if the 3rd letter is &, So it's above the first 9 letters
                {

                    switch(s[i][j])
                    {
                        case '1':switch(s[i][j+1])          // some probabilities if the first number is 1
                        {
                        case '0':o[i][k]='j';break;
                        case '1':o[i][k]='k';break;
                        case '2':o[i][k]='l';break;
                        case '3':o[i][k]='m';break;
                        case '4':o[i][k]='n';break;
                        case '5':o[i][k]='o';break;
                        case '6':o[i][k]='p';break;
                        case '7':o[i][k]='q';break;
                        case '8':o[i][k]='r';break;
                        case '9':o[i][k]='s';break;
                        }break;

                        case '2':switch(s[i][j+1])              // some other probabilities if the first num is 2
                        {
                        case '0':o[i][k]='t';break;
                        case '1':o[i][k]='u';break;
                        case '2':o[i][k]='v';break;
                        case '3':o[i][k]='w';break;
                        case '4':o[i][k]='x';break;
                        case '5':o[i][k]='y';break;
                        case '6':o[i][k]='z';break;
                        }break;
                    }
                    j+=2;k++;
                }

                else                                        // or it's in the first 9 letters
                {

                    switch(s[i][j])
                    {
                        case '1':o[i][k]='a';break;
                        case '2':o[i][k]='b';break;
                        case '3':o[i][k]='c';break;
                        case '4':o[i][k]='d';break;
                        case '5':o[i][k]='e';break;
                        case '6':o[i][k]='f';break;
                        case '7':o[i][k]='g';break;
                        case '8':o[i][k]='h';break;
                        case '9':o[i][k]='i';break;
                    }
                    k++;
                }

            }
    }
    for(int i=0;i<q;i++)                                                // printing the output
        puts(o[i]);


}



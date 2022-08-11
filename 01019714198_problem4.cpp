#include <iostream>
using namespace std;
int Array[30][100000],C[30][100000]={0};                // declaration the array of the creatures' heights and the array of their vision
int main()
{
    int N,q;                                             // declaration of num of creatures
    cin>>q;                                             // getting the num of test cases

    for(int i=0;i<q;i++)
    {

        cin>>N;                                         // initialization the number of creatures

        for(int j=0;j<N;j++)
            cin>>Array[i][j];                           // initialization the height of every creature

        for(int j=0;j<N-1;j++)                          // calculating the number of creature every one of them is seeing
            for(int k=j+1;k<N;k++)
        {

            if(Array[i][j]>Array[i][k])
            {
                if(Array[i][k]<Array[i][k+1])
                    C[i][j]++;
            }

            else
            {
                C[i][j]++;
                break;
            }
        }
    }

    for(int i=0;i<q;i++)                                        // printing the output
        for(int j=0;j<N;j++)
            cout<<C[i][j]<<" ";
}



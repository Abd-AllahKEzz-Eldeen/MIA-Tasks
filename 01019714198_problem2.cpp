#include <iostream>
using namespace std;
int main(void)
{
    int q;
    int P,H;
    float hp[30];
    cin>> q;                        // receiving the number of test cases

    for(int i =0;i<q;i++)
    {

        cin>> hp[i]>>P>>H;

        for(int j=0;j<P;j++)
            hp[i]=hp[i]/2.0+10;             // calculating the hp after the plasma blast weapon

        for(int j=0;j<H;j++)
            hp[i]-=10;                      // calculating the hp after the hellfire force weapon
    }

    for(int i=0;i<q;i++)

        if(hp[i]>0)
            cout << "NO\n";                    // determine whether the creature is still alive

        else
            cout << "YES\n";                    // if the hp<=0,so it's gone away
}

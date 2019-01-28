/* Author : Mohamed Ahmed (MohamedAhmed04)

   contest name : COCI 16 contest 1
   problem name : Tarifa (COCI 16-Tarifa)
   problem link : https://oj.uz/problem/view/COCI16_tarifa

   loop on days and add x everyday and subtract from it usage of that day
   and after that print remaining usage + x.
*/

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int x , n ;
    cin>>x>>n;
    int now = 0 ;
    for(int i = 0 ; i < n ; ++i)
    {
        now += x ;
        int a ;
        cin>>a ;
        now -= a ;
    }
    return cout<<now+x<<"\n" , 0 ;
}

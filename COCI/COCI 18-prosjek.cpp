/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : COCI 2017/2018 contest 7
   problem name : prosjek (COCI 18-prosjek)
   problem link : https://oj.uz/problem/view/COCI18_prosjek

   explanation of the problem : we should every time choose two numbers
   and erase them and write their average and print last number remained.
   so we will make n-1 steps

   problem solution : to have highest average so we need to
   sort them in increasing order then set average as arr[0]
   and after that average will be (average + arr[i]) / 2.00.

*/


#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n ;
    cin>>n ;
    int arr[n] ;
    for(int i = 0 ; i < n ; ++i)
        cin>>arr[i] ;
    sort(arr , arr + n) ;
    double ans = arr[0] ;
    for(int i = 1 ; i < n ; ++i)
        ans = (ans + arr[i]*1.00) / 2.00 ;
    return cout<<fixed<<setprecision(12)<<ans<<"\n" , 0 ;
}

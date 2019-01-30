/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest name : COCI 14 contest 1
   problem name : Klopska (COCI 14-Klopska)
   problem link : https://dmoj.ca/problem/coci14c1p2

   since side length will be equal to max(max difference between two x ,
   max difference between two y)..then area of this two conditions and print maximum
   of them.
*/

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n ;
    cin>>n ;
    int arr[n] , arr1[n] ;
    for(int i = 0 ; i < n ; ++i)
        cin>>arr[i]>>arr1[i] ;
    int x = *max_element(arr , arr + n) - *min_element(arr , arr + n) ;
    x *= x ;
    int y = *max_element(arr1 , arr1 + n) - *min_element(arr1 , arr1 + n) ;
    y *= y ;
    return cout<<max(x , y)<<"\n" , 0 ;
}

/* Author : Mohamed Ahmed (MohamedAhmed04)

   contest name : COCI 14 contest 5
   problem name : Funghi (COCI 14-Funghi)
   problem link : https://dmoj.ca/problem/coci14c5p1

   bruteforce on every possible half and print maximum of them
*/

#include <iostream>

using namespace std;

int main()
{
    int n = 8 ;
    int arr[n] ;
    for(int i = 0 ; i < n ; ++i)
        cin>>arr[i] ;
    int MAX = 0 ;
    for(int i = 0 ; i < n ; ++i)
    {
        int sum = 0 ;
        for(int j = 0 ; j < 4 ; ++j)
            sum += arr[((i+j)%n)];
        MAX = max(MAX , sum) ;
    }
    return cout<<MAX<<"\n" , 0 ;
}

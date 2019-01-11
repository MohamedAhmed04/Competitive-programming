/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest : AtCoder dp Educational contest (Atcoder dp)
   problem name : dp_a - Frog1
   problem link : https://atcoder.jp/contests/dp/tasks/dp_a

*/

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n ;
    cin>>n ;
    int arr[n] , dp[n];
    for(int i = 0 ; i < n ; ++i)
        cin>>arr[i] ;
    dp[n-1] = 0 ;
    for(int j = n-2 ; j >= 0 ; --j)
    {
        if(j == n-2)
            dp[j] = abs(arr[n-1] - arr[j]);
        else
            dp[j] = min(dp[j+1] + abs(arr[j+1] - arr[j]) , dp[j+2] + abs(arr[j+2] - arr[j]));
    }
    return cout<<dp[0]<<"\n" , 0 ;
}

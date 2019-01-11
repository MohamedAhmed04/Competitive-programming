/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest : AtCoder dp Educational contest (Atcoder dp)
   problem name : dp_c - Vacation
   problem link : https://atcoder.jp/contests/dp/tasks/dp_c

*/

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n ;
    cin>>n ;
    int arr[n] , arr1[n] , arr2[n] ;
    for(int i = 0 ; i < n ; ++i)
        cin>>arr[i]>>arr1[i]>>arr2[i] ;
    int dp[n][3] ;
    for(int i = 0 ; i < n ; ++i)
    {
        if(i == 0)
            dp[i][0] = arr[i] , dp[i][1] = arr1[i] , dp[i][2] = arr2[i];
        else
        {
            dp[i][0] = max(dp[i-1][1] , dp[i-1][2]) + arr[i] ;
            dp[i][1] = max(dp[i-1][0] , dp[i-1][2]) + arr1[i] ;
            dp[i][2] = max(dp[i-1][0] , dp[i-1][1]) + arr2[i] ;
        }
    }
    return cout<<max(dp[n-1][0] , max(dp[n-1][1] , dp[n-1][2]))<<"\n" , 0 ;
}

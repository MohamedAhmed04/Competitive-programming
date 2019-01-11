/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest : AtCoder dp Educational contest (Atcoder dp)
   problem name : dp_e - Knapsack2
   problem link : https://atcoder.jp/contests/dp/tasks/dp_e

*/

#include <bits/stdc++.h>

using namespace std ;

const int MAX = 110 , MAX2 = 1e5 + 10 ;
const long long inf = 1e17 ;
long long dp[MAX][MAX2] ;
long long arr[MAX] , arr2[MAX] ;
long long n , w ;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    memset(dp , -1 , sizeof(dp));
    cin>>n>>w ;
    long long sum = 0 ;
    for(int i = 0 ; i < n ; ++i)
    {
        cin>>arr[i]>>arr2[i] ;
        sum += arr2[i] ;
    }
    for(int i = 0 ; i < n ; ++i)
    {
        for(int j = 0 ; j <= sum ; ++j)
            dp[i][j] = inf ;
    }
    for(int i = 0 ; i < n ; ++i)
        dp[i][arr2[i]] = arr[i] , dp[i][0] = 0;
    for(int i = 1 ; i < n ; ++i)
    {
        for(int j = 1 ; j <= sum ; ++j)
        {
            dp[i][j] = min(dp[i][j] , dp[i-1][j]);
            if(dp[i-1][j] != inf)
            {
                dp[i][j+arr2[i]] = min(dp[i][j + arr2[i]] , dp[i-1][j] + arr[i]);
            }
        }
    }
    long long ans = 0 ;
    for(int i = 0 ; i < n ; ++i)
    {
        for(int j = 0 ; j <= sum ; ++j)
        {
            if(dp[i][j] <= w)
                ans = max(ans , j*1ll) ;
        }
    }
    return cout<<ans<<"\n" , 0 ;
}

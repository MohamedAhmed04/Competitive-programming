/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest : AtCoder dp Educational contest (Atcoder dp)
   problem name : dp_m - Candies
   problem link : https://atcoder.jp/contests/dp/tasks/dp_m

*/

#include <bits/stdc++.h>

using namespace std;

const long long mod = 1e9 + 7ll ;
const int MAX = 100010 , N = 110 ;
long long dp[MAX][N] , dp2[MAX][N] ;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n , k ;
    cin>>n>>k ;
    long long arr[n+1] ;
    for(int i = 1 ; i <= n ; ++i)
        cin>>arr[i] ;
    for(int i = 0 ; i <= k ; ++i)
    {
        for(int j = 1 ; j <= n ; ++j)
        {
            if(j == 1)
            {
                if(i <= arr[j])
                    dp[i][j] = 1ll ;
            }
            else if(i - arr[j] <= 0)
                dp[i][j] = dp2[i][j-1] % mod;
            else
                dp[i][j] = (dp2[i][j-1] - dp2[i-arr[j]-1][j-1] + mod) % mod ;
            if(i == 0)
                dp2[i][j] = 1ll ;
            else
                dp2[i][j] = (dp[i][j] + dp2[i-1][j]) % mod ;
        }
    }
    return cout<<dp[k][n]<<"\n" , 0 ;
}

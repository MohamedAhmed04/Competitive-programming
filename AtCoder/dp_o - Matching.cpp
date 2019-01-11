/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest : AtCoder dp Educational contest (Atcoder dp)
   problem name : dp_o - Matching
   problem link : https://atcoder.jp/contests/dp/tasks/dp_o

*/

#include <bits/stdc++.h>

using namespace std;

const long long mod = 1e9 + 7ll ;
const int N = 21 ;
const int MAX = 1ll << N ;
long long dp[N][MAX] ;
int arr[N][N] ;
int n ;

long long solve(int idx , int mask)
{
    if(idx == n)
    {
        if(mask == (1 << n)-1)
            return 1 ;
        return 0 ;
    }
    long long &ret = dp[idx][mask] ;
    if(ret != -1)
        return ret ;
    ret = 0 ;
    for(int j = 0 ; j < n ; ++j)
    {
        if(arr[idx][j] == 1 && ((mask & (1 << j)) == 0))
            ret = (ret + solve(idx+1 , mask | (1ll << j))) % mod ;
    }
    ret = (ret % mod) ;
    return ret ;
}

int main()
{
    memset(dp , -1 , sizeof(dp));
    scanf("%d" , &n);
    for(int i = 0 ; i < n ; ++i)
    {
        for(int j = 0 ; j < n ; ++j)
            scanf("%d" , &arr[i][j]);
    }
    return printf("%lld\n" , solve(0 , 0)) , 0 ;
}

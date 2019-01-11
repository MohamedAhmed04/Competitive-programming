/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest : AtCoder dp Educational contest (Atcoder dp)
   problem name : dp_l - Deque
   problem link : https://atcoder.jp/contests/dp/tasks/dp_l

*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 3010 ;
long long arr[MAX] ;
long long dp[MAX][MAX][2] ;
int n ;

long long solve(int l , int r , int turn)
{
    if(l > r || r < l)
        return 0 ;
    long long &ret = dp[l][r][turn] ;
    if(ret != -1)
        return ret ;
    if(turn == 0)
    {
        long long choice1 = solve(l+1 , r , 1) + arr[l] ;
        long long choice2 = solve(l , r-1 , 1) + arr[r] ;
        ret = max(choice1 , choice2);
        return ret ;
    }
    else if(turn == 1)
    {
        long long choice1 = solve(l+1 , r , 0) - arr[l] ;
        long long choice2 = solve(l , r-1 , 0) - arr[r] ;
        ret = min(choice1 , choice2);
        return ret ;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    memset(dp , -1 , sizeof(dp));
    cin>>n ;
    for(int i = 0 ; i < n ; ++i)
        cin>>arr[i] ;
    return cout<<solve(0 , n-1 , 0)<<"\n" , 0 ;
}

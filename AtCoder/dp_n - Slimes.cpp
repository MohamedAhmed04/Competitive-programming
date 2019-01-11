/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest : AtCoder dp Educational contest (Atcoder dp)
   problem name : dp_n - Slimes
   problem link : https://atcoder.jp/contests/dp/tasks/dp_n

*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 410 ;
long long arr[MAX] , dp[MAX][MAX] ;

long long solve(int l , int r)
{
    if(l == r)
        return 0 ;
    if(l > r)
        return 1e16 ;
    if(r-l == 1)
        return (arr[l] + arr[r]) ;
    long long &ret = dp[l][r] ;
    if(ret != -1)
        return ret ;
    ret = 1e15 ;
    long long sum = 0 ;
    for(int i = l ; i < r ; ++i)
        ret = min(ret , solve(l , i) + solve(i+1 , r)) , sum += arr[i];
    sum += arr[r] ;
    ret = ret + sum ;
    return ret ;
}

int main()
{
    memset(dp , -1 , sizeof(dp));
    int n ;
    cin>>n ;
    for(int i = 0 ; i < n ; ++i)
        cin>>arr[i] ;
    return cout<<solve(0 , n-1)<<"\n" , 0 ;
}

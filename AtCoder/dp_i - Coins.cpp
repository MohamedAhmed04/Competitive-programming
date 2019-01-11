/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest : AtCoder dp Educational contest (Atcoder dp)
   problem name : dp_i - Coins
   problem link : https://atcoder.jp/contests/dp/tasks/dp_i

*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 3010 ;
long double dp[MAX][MAX] ;
int n ;
long double arr[MAX] ;

long double solve(int idx , int h)
{
    if(idx == n)
    {
        if(h >= (n+1)/2)
            return 1.00;
        else
            return 0.00 ;
    }
    long double &ret = dp[idx][h] ;
    if(fabs(ret+1) > 1e-9)
        return ret ;
    ret = arr[idx] * solve(idx+1 , h+1) ;
    ret += (1 - arr[idx]) * solve(idx+1 , h) ;
    return ret ;
}

int main()
{
    memset(dp , -1 , sizeof(dp));
    cin>>n ;
    for(int i = 0 ; i < n ; ++i)
        cin>>arr[i] ;
    return cout<<fixed<<setprecision(12)<<solve(0 , 0)<<"\n" , 0 ;
}

/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest : AtCoder dp Educational contest (Atcoder dp)
   problem name : dp_d - Knapsack 1
   problem link : https://atcoder.jp/contests/dp/tasks/dp_d

*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 105 ;
const int MAX2 = 1e5+10 ;
long long arr[MAX] , arr2[MAX] ;
long long dp[MAX][MAX2];
int n , w ;

long long solve(int idx , long long rem)
{
    if(idx == n)
        return 0 ;
    long long &ret = dp[idx][rem] ;
    if(ret != -1)
        return ret ;
    long long choice1 = solve(idx+1 , rem) ;
    long long choice2 = -1e17 ;
    if(rem - arr[idx] >= 0)
        choice2 = solve(idx+1 , rem - arr[idx]) + arr2[idx] ;
    return (ret = max(choice1 , choice2));
}

int main()
{
    memset(dp , -1 , sizeof(dp));
    cin>>n>>w ;
    for(int i = 0 ; i < n ; ++i)
        cin>>arr[i]>>arr2[i] ;
    return cout<<solve(0 , w)<<"\n" , 0 ;
}

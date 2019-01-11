/* Author : Mohamed Ahmed (handle : MohamedAhmed04)

   contest : AtCoder dp Educational contest (Atcoder dp)
   problem name : dp_h - Grid1
   problem link : https://atcoder.jp/contests/dp/tasks/dp_h

*/

#include <bits/stdc++.h>

using namespace std;


const long long mod = 1e9 + 7 ;
const int MAX = 1010 ;
long long dp[MAX][MAX] ;
int n , m ;
char arr[MAX][MAX];

bool check(int x , int y)
{
    return (x >= 0 && x < n && y >= 0 && y < m && arr[x][y] == '.') ;
}

long long solve(int x , int y)
{
    if(x == n-1 && y == m-1)
        return 1ll ;
    long long &ret = dp[x][y] ;
    if(ret != -1)
        return ret ;
    ret = 0;
    if(check(x+1,y))
        ret = (ret + solve(x+1 , y)) % mod;
    if(check(x , y+1))
        ret = (ret + solve(x , y+1)) % mod;
    return ret ;
}

int main()
{
    memset(dp , -1 , sizeof(dp));
    cin>>n>>m ;
    for(int i = 0 ; i < n ; ++i)
        for(int j = 0 ; j < m ; ++j)
            cin>>arr[i][j] ;
    return cout<<solve(0 , 0)<<"\n" , 0 ;
}

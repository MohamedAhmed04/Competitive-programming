/* Author : Mohamed Ahmed Bakry (handle : MohamedAhmed04)

   contest name : USACO 2017 January contest
   problem name : Subsequence Reversal (USACO 2017 January contest - platinum - problem 3 - Subsequence Reversal)
   problem link : http://usaco.org/index.php?page=viewproblem2&cpid=698

   problem solution :
    http://usaco.org/current/data/sol_subrev_platinum_jan17.html

*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 55 ;
int arr[MAX] ;
int n ;
int dp[MAX][MAX][MAX][MAX] ;

int solve(int i , int j , int x , int y)
{
    if(x > y)
        return (-1e9) ;
    if(i > j)
        return 0 ;
    int &ret = dp[i][j][x][y] ;
    if(ret != -1)
        return ret ;
    if(i == j)
    {
        if(arr[i] >= x && arr[i] <= y)
            return 1 ;
        else
            return 0 ;
    }
    ret = 0 ;
    if(arr[i] <= y)
        ret = max(ret , solve(i+1 , j-1 , x , arr[i]) + 1) ;
    if(arr[j] >= x)
        ret = max(ret , solve(i+1 , j-1 , arr[j] , y) + 1) ;
    if(arr[j] >= x && arr[i] <= y)
        ret = max(ret , solve(i+1 , j-1 , arr[j] , arr[i]) + 2) ;
    ret = max(ret , solve(i+1 , j , x , y)) ;
    if(arr[i] >= x)
        ret = max(ret , solve(i+1 , j , arr[i] , y) + 1) ;
    ret = max(ret , solve(i , j-1 , x , y)) ;
    if(arr[j] <= y)
        ret = max(ret , solve(i , j-1 , x , arr[j]) + 1) ;
    return ret ;
}

int main()
{
    freopen("subrev.in" , "r" , stdin) ;
    freopen("subrev.out" , "w" , stdout) ;
    memset(dp , -1 , sizeof(dp)) ;
    scanf("%d" , &n) ;
    for(int i = 0 ; i < n ; ++i)
        scanf("%d" , &arr[i]) ;
    return cout<<solve(0 , n-1 , 0 , 50)<<"\n" , 0 ;
}
